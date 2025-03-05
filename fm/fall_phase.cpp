#include "fall_phase.hpp"
#include <cmath>

// どれだけ巻いたかを記録するための変数
int right_count = 0; // 右に曲がった時のカウント
int left_count = 0;  // 左に曲がった時のカウント

int basic_right_count = 0;
int basic_left_count = 0;

constexpr double radius_e = 6378000; // 地球半径(m)

// degreeからradへの変換
// double deg_to_rad(const double &num) { return num * M_PI / 180.0; }

// 緯度経度を平面直角座標に変換する(chatGPTくんにやってもらった。自分で書いたのは一番下にある。)
// std::pair<double, double> calc_xy(double phi_deg, double lambda_deg, double phi0_deg, double lambda0_deg) {
//   // 緯度経度・平面直角座標系原点をラジアンに直す
//   double phi_rad = phi_deg * M_PI / 180.0;
//   double lambda_rad = lambda_deg * M_PI / 180.0;
//   double phi0_rad = phi0_deg * M_PI / 180.0;
//   double lambda0_rad = lambda0_deg * M_PI / 180.0;

//   // 補助関数
//   auto A_array = [](double n) {
//     std::array<double, 6> A = {
//         1 + std::pow(n, 2) / 4. + std::pow(n, 4) / 64.,
//         -(3. / 2) * (n - std::pow(n, 3) / 8. - std::pow(n, 5) / 64.),
//         (15. / 16) * (std::pow(n, 2) - std::pow(n, 4) / 4.),
//         -(35. / 48) * (std::pow(n, 3) - (5. / 16) * std::pow(n, 5)),
//         (315. / 512) * std::pow(n, 4),
//         -(693. / 1280) * std::pow(n, 5)};
//     return A;
//   };

//   auto alpha_array = [](double n) {
//     std::array<double, 6> alpha = {
//         std::nan(""),
//         (1. / 2) * n - (2. / 3) * std::pow(n, 2) + (5. / 16) * std::pow(n, 3) +
//             (41. / 180) * std::pow(n, 4) - (127. / 288) * std::pow(n, 5),
//         (13. / 48) * std::pow(n, 2) - (3. / 5) * std::pow(n, 3) +
//             (557. / 1440) * std::pow(n, 4) + (281. / 630) * std::pow(n, 5),
//         (61. / 240) * std::pow(n, 3) - (103. / 140) * std::pow(n, 4) +
//             (15061. / 26880) * std::pow(n, 5),
//         (49561. / 161280) * std::pow(n, 4) - (179. / 168) * std::pow(n, 5),
//         (34729. / 80640) * std::pow(n, 5)};
//     return alpha;
//   };

//   // 定数 (a, F: 世界測地系-測地基準系1980（GRS80）楕円体)
//   double m0 = 0.9999;
//   double a = 6378137.;
//   double F = 298.257222101;

//   // (1) n, A_i, alpha_iの計算
//   double n = 1. / (2 * F - 1);
//   auto A = A_array(n);
//   auto alpha = alpha_array(n);

//   // (2), S, Aの計算
//   double A_ = (m0 * a) / (1. + n) * A[0]; // [m]
//   double S_ =
//       (m0 * a) / (1. + n) *
//       (A[0] * phi0_rad + A[1] * std::sin(2 * phi0_rad) +
//        A[2] * std::sin(4 * phi0_rad) + A[3] * std::sin(6 * phi0_rad) +
//        A[4] * std::sin(8 * phi0_rad) + A[5] * std::sin(10 * phi0_rad)); // [m]

//   // (3) lambda_c, lambda_sの計算
//   double lambda_c = std::cos(lambda_rad - lambda0_rad);
//   double lambda_s = std::sin(lambda_rad - lambda0_rad);

//   // (4) t, t_の計算
//   double t = std::sinh(
//       std::atanh(std::sin(phi_rad)) -
//       ((2 * std::sqrt(n)) / (1 + n)) *
//           std::atanh(((2 * std::sqrt(n)) / (1 + n)) * std::sin(phi_rad)));
//   double t_ = std::sqrt(1 + t * t);

//   // (5) xi', eta'の計算
//   double xi2 = std::atanh(t / lambda_c); // [rad]
//   double eta2 = std::atanh(lambda_s / t_);

//   // (6) x, yの計算
//   double x =
//       A_ * (xi2 + alpha[1] * std::sin(2 * xi2) + alpha[2] * std::sin(4 * xi2) +
//             alpha[3] * std::sin(6 * xi2) + alpha[4] * std::sin(8 * xi2) +
//             alpha[5] * std::sin(10 * xi2)) -
//       S_; // [m]
//   double y =
//       A_ * (eta2 + alpha[1] * std::cos(2 * xi2) + alpha[2] * std::cos(4 * xi2) +
//             alpha[3] * std::cos(6 * xi2) + alpha[4] * std::cos(8 * xi2) +
//             alpha[5] * std::cos(10 * xi2)); // [m]

//   return {x, y}; // [m]
// }

//三角関数verのcalc_xy
std::pair<double,double> calc_xy(double phi_deg, double lambda_deg, double
phi0_deg, double lambda0_deg){
    double difference_lon = lambda_deg - lambda0_deg;
    double difference_lat = phi_deg - phi0_deg;
    double x = difference_lon*radius_e;
    double y = difference_lat*radius_e;
    return{x,y};
}

// 時計回りに回転する関数
std::pair<double, double>Rotation_clockwise_xy(std::pair<double, double> vec_xy, double radian) {
  double sin_rad = std::sin(radian);
  double cos_rad = std::cos(radian);
  double new_vector_x = vec_xy.first * cos_rad + vec_xy.second * sin_rad;
  double new_vector_y = vec_xy.second * cos_rad - vec_xy.first * sin_rad;

  return {new_vector_x, new_vector_y};
}

void fall_phase(Phase &phase, Flash &flash, BMP280 &bmp280, BNO055 &bno055,
                GPS &gps, const Servo &servo_r, const Servo &servo_l) {
  //------ちゃんと動くか確認するためのコード-----
  // std::vector<float> mag_vector = {0.0,0.0,0.0};
  // auto gps_data_goal = {0.0,0.0};//{lon,lat}で入っている想定
  // auto gps_data_cansat = {0.0,0.0};
  //-------------------------------------------
  //------本番用のコード------------------------
  auto bno_data = bno055.read(); //{accel,grv,mag}の順番で入っている想定
  auto gps_data = gps.read();
  auto bmp_data = bmp280.read();
  std::pair<double, double> gps_data_cansat = {gps_data.lat, gps_data.lon};
  std::pair<double, double> gps_data_goal = {30.414138,
                                             130.904127}; // ここは自分で入力
  //-------------------------------------------

  // 処理に使うデータ
  double g_lon = std::get<0>(gps_data_goal);   // ゴールの経度
  double g_lat = std::get<1>(gps_data_goal);   // ゴールの緯度
  double c_lon = std::get<0>(gps_data_cansat); // 自分の経度
  double c_lat = std::get<1>(gps_data_cansat); // 自分の緯度
  std::pair<double, double> North_xy = {bno_data.accel[0], bno_data.accel[1]}; // cansatから見た北の方向(xy平面)
  std::pair<double, double> Cansat_forward_xy = {1.0,0.0}; // 正面をx軸の方としている(これはbnoの向き次第、違ったら適宜変更)
  // cansatを原点とした座標でgoalを表す
  std::pair<double, double> goal_xy = calc_xy(g_lat, g_lon, c_lat, c_lon);
  // 距離を求める
  double distance = std::sqrt((goal_xy.first) * (goal_xy.first) + (goal_xy.second) * (goal_xy.second));
  printf("distance: %f\n", distance);
  _flash.write("distance: %f\n", distance);
  // 方角基底(北がx軸の右手系)からCansat基底(正面がx軸の右手系)にgoal_xyを変換----------------------
  // step1:北がx軸になるように変換(現在は東がx軸なので、基底を90°だけ反時計回りに回転⇔成分を90°だけ時計回りに回転)
  std::pair<double, double> goal_xy_north_basis = Rotation_clockwise_xy(goal_xy, M_PI / 2);
  // step2:方角基底からcansat基底に変換
  // step2-1:北が正面から見て何度反時計回りにズレているかを計算
  double North_angle_cansat_basis = std::atan2(North_xy.second, North_xy.first) - std::atan2(Cansat_forward_xy.second, Cansat_forward_xy.first);
  // step2-2:ズレている分だけ基底を回転させる(成分は反時計回転なので-1をかけてあげる)
  std::pair<double, double> goal_xy_cansat_basis = Rotation_clockwise_xy(goal_xy_north_basis, -1 * North_angle_cansat_basis);
  //------------------------------------------------------------------------------------------
  // ここまでの操作で、Cansat正面をx軸とした基底でgoalの方向を定めることができた。
  // あとは、その角度からどっちに舵を取ればいいかを決めればよい。
  // 角度を求める(0~2PI)
  double goal_angle_cansat_basis = std::atan2(goal_xy_cansat_basis.second, goal_xy_cansat_basis.first);
  goal_angle_cansat_basis = goal_angle_cansat_basis + M_PI;
  printf("angle: %f\n", goal_angle_cansat_basis);
  _flash.write("angle: %f\n", goal_angle_cansat_basis);
  // 角度から指示を出す。
  // 要変更！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
  // 遠距離フェーズもどきver---------------------------------------------------
  if ((3 * M_PI / 4) <= goal_angle_cansat_basis &&
      goal_angle_cansat_basis < (5 * M_PI / 4)) // 正面にゴールがある時の指示
  {
    while (right_count != 0 && left_count != 0) // もう巻き取っている場合はより戻して左右均等にする。
    {
      if (right_count > 0) {
        servo_r.left_turn();
        sleep_ms(2000);
        right_count = right_count - 1;
        servo_r.stop_turn();
      }
      if (left_count > 0) {
        servo_l.right_turn();
        sleep_ms(2000);
        left_count = left_count - 1;
        servo_l.stop_turn();
      }
    }
  } else if ((1 * M_PI / 4) <= goal_angle_cansat_basis && goal_angle_cansat_basis < (3 * M_PI / 4)) // 右にゴールがあるときの指示
  {
    servo_r.right_turn();
    sleep_ms(2000);
    right_count = right_count + 1;
    servo_r.stop_turn();

  } else if ((5 * M_PI / 4) <= goal_angle_cansat_basis && goal_angle_cansat_basis < (7 * M_PI / 4)) // 左にゴールがあるときの指示
  {
    servo_l.left_turn();
    sleep_ms(2000);
    left_count = left_count + 1;
    servo_l.stop_turn();

  } else if (goal_angle_cansat_basis < (1 * M_PI / 4) || (7 * M_PI / 4) <= goal_angle_cansat_basis) // 後ろにゴールがあるときの指示
  {
    servo_r.right_turn();
    sleep_ms(4000);
    right_count = right_count + 2;
    servo_r.stop_turn();
  }

  if (distance < 10) {
    phase = Phase::Goal;
    printf("enter goal_phase");
    sleep_ms(5000);
  }
  if (g_lat < c_lat) {
    phase = Phase::Goal;
    printf("enter goal_phase");
    sleep_ms(5000);
  }
}

// 加速度(進行方向)考慮ver---------------------------------------------------
//  //加速度の方向
//  std::pair<double, double> forward_accel = {bno_data[0][0],bno_data[0][1]};
//  std::pair<double, double> forward_accel_goal_basis =
//  Rotation_clockwise_xy(forward_accel,goal_angle_cansat_basis); double
//  accel_angle_goal_basis =
//  atan2(forward_accel_goal_basis[1],forward_accel_goal_basis[0]);
//  if(accel_angle_goal_basis>(M_PI/4)){
//      basic_right_count = 1;
//      basic_left_count = 0;
//      if(right_count>basic_right_count){
//          s35_left.left_turn();
//          sleep_ms(2000);
//          right_count = right_count - 1;
//      }else if(right_count<basic_right_count){
//          s35_left.right_turn();
//          sleep_ms(2000);
//          right_count = right_count + 1;
//      }else{
//          break;
//      }
//      if (left_count>basic_left_count)
//      {
//          s35_right.right_turn();
//          sleep_ms(2000);
//          left_count = left_count - 1;
//      }else if(left_count<basic_left_count){
//          s35_right.right_turn();
//          sleep_ms(2000);
//          left_count = left_count + 1;
//      }
//      else{
//          break;
//      }
//  }else if(accel_angle_goal_basis>(-1*M_PI/4)){
//      basic_right_count = 0;
//      basic_left_count = 1;
//      if(right_count>basic_right_count){
//          s35_left.left_turn();
//          sleep_ms(2000);
//          right_count = right_count - 1;
//      }else if(){right_count<basic_right_count
//          s35_left.right_turn();
//          sleep_ms(2000);
//          right_count = right_count + 1;
//      }else{
//          break;
//      }
//      if (left_count>basic_left_count)
//      {
//          s35_right.right_turn();
//          sleep_ms(2000);
//          left_count = left_count - 1;
//      }else if(left_count<basic_left_count){
//          s35_right.right_turn();
//          sleep_ms(2000);
//          left_count = left_count + 1;
//      }else{
//          break;
//      }
//  }

// if ((3*M_PI/4) <= goal_angle_cansat_basis && goal_angle_cansat_basis <
// (5*M_PI/4))//正面にゴールがある時の指示
// {
//     while (right_count!= basic_right_count &&
//     left_count!=basic_left_count)//もう巻き取っている場合はより戻して左右均等にする。
//     {
//         if(right_count>basic_right_count){
//             s35_left.left_turn();
//             sleep_ms(2000);
//             right_count = right_count - 1;
//         }else if(right_count<basic_right_count){
//             s35_left.right_turn();
//             sleep_ms(2000);
//             right_count = right_count + 1;
//         }else{
//             break;
//         }
//         if (left_count>basic_left_count)
//         {
//             s35_right.right_turn();
//             sleep_ms(2000);
//             left_count = left_count - 1;
//         }else if(left_count<basic_left_count){
//             s35_right.right_turn();
//             sleep_ms(2000);
//             left_count = left_count + 1;
//         }else{
//             break;
//         }
//     }
// }else if((1*M_PI/4) <= goal_angle_cansat_basis && goal_angle_cansat_basis <
// (3*M_PI/4))//右にゴールがあるときの指示
// {
//     s35_left.right_turn();
//     sleep_ms(2000);
//     right_count = right_count + 1;
// }else if((5*M_PI/4) <= goal_angle_cansat_basis && goal_angle_cansat_basis <
// (7*M_PI/4))//左にゴールがあるときの指示
// {
//     s35_right.left_turn();
//     sleep_ms(2000);
//     left_count = left_count + 1;
// }else if(goal_angle_cansat_basis < (1*M_PI/4)||(7*M_PI/4) <=
// goal_angle_cansat_basis)//後ろにゴールがあるときの指示
// {
//     s35_left.right_turn();
//     sleep_ms(4000);
//     right_count = right_count + 2;
// }

// 自分で書いたはいいものの、自信がなくなって没になった関数たちの墓場

/*
//
補助関数(4.という書き方をしているのは4をdouble型で表すため。powよりも*でかけたほうが速いという)
std::vector<double> cal_A_array(double n) {
    double A0 = 1 + (n*n)/4. + (n*n*n*n)/64.;
    double A1 = - (3./2) * ( n - (n*n*n)/8. - (n*n*n*n*n)/64. );
    double A2 = (15./16) * ( n*n - (n*n*n*n)/4. );
    double A3 = - (35./48) * ( n*n*n - (5./16) * (n*n*n*n*n) );
    double A4 = (315./512) * ( n*n*n*n );
    double A5 = -(693./1280) * ( n*n*n*n*n );
    return {A0, A1, A2, A3, A4, A5};
}

std::vector<double> cal_alpha_array(double n) {
    double a0 = std::nan(""); //
dummy,vectorの長さを6にするために置いてるらしい...おいらにはよくわからない
    double a1 = (1.0/2.0)*n - (2.0/3.0)*(n*n) + (5.0/16.0)*(n*n*n) +
(41.0/180.0)*(n*n*n*n) - (127.0/288.0)*(n*n*n*n*n); double a2 =
(13.0/48.0)*(n*n) - (3.0/5.0)*(n*n*n) + (557.0/1440.0)*(n*n*n*n) +
(281.0/630.0)*(n*n*n*n*n); double a3 = (61.0/240.0)*(n*n*n) -
(103.0/140.0)*(n*n*n*n) + (15061.0/26880.0)*(n*n*n*n*n); double a4 =
(49561.0/161280.0)*(n*n*n*n) - (179.0/168.0)*(n*n*n*n*n); double a5 =
(34729.0/80640.0)*(n*n*n*n*n);

    return {a0, a1, a2, a3, a4, a5};
}

// 2次元のベクトルをxy平面で時計回りに回転する関数
std::vector<double> Rotation_clockwise_xy(std::vector<double> vec, double
Radian) { double sin_rad = std::sin(Radian); double cos_rad = std::cos(Radian);
    double new_vector_x = vec[0] * cos_rad + vec[1] * sin_rad;
    double new_vector_y = vec[1] * cos_rad - vec[0] * sin_rad;
    std::vector<double> new_vector = {new_vector_x,new_vector_y};
    return new_vector;
}

//距離を求める関数
std::vector<double> calc_xy(double phi_deg,double lambda_deg,double
phi0_deg,double lambda0_deg){
    //  緯度経度を平面直角座標に変換する
    // - input:
    //     (phi_deg, lambda_deg):
変換したい緯度・経度[度]（分・秒でなく小数であることに注意）
    //     (phi0_deg, lambda0_deg):
平面直角座標系原点の緯度・経度[度]（分・秒でなく小数であることに注意）
    // - output:
    //     x: 変換後の平面直角座標[m]
    //     y: 変換後の平面直角座標[m]
    //-------------------------------------------
    //緯度経度・平面直角座標系原点をラジアンに直す
    double phi_rad = deg_to_rad(phi_deg);
    double lambda_rad = deg_to_rad(lambda_deg);
    double phi0_rad = deg_to_rad(phi0_deg);
    double lambda0_rad = deg_to_rad(lambda0_deg);

    //定数 (a, F: 世界測地系-測地基準系1980（GRS80）楕円体)
    constexpr double m0 = 0.9999;
    constexpr double a = 6378137;
    constexpr double F = 298.257222101;

    //(1) n, A_i, alpha_iの計算
    double n = 1. / (2*F - 1);
    std::vector<double> A_array_6 = cal_A_array(n);//要素6つ
    std::vector<double> alpha_array_6 = cal_alpha_array(n);//要素6つ

    //(2), S, Aの計算(改良の余地あり)
    double A_ = ( (m0*a)/(1.+n) )*A_array_6[0]; // [m]
    std::vector<double> A_array_5 = A_array_6;//コピー
    A_array_5.erase(A_array_5.begin());//始めの要素を消す(これで要素5つに)
    std::vector<double> array_sin =
{std::sin(2*phi0_rad*1),std::sin(2*phi0_rad*2),std::sin(2*phi0_rad*3),std::sin(2*phi0_rad*4),std::sin(2*phi0_rad*5)};//chu!冗長でごめん!
    double dot_array5_arraysin = std::inner_product(A_array_5,array_sin);
    double S_ = ( (m0*a)/(1.+n) )*( A_array_6[0]*phi0_rad + dot_array5_arraysin
); // [m]

    //(3) lambda_c, lambda_sの計算
    double lambda_c = std::cos(lambda_rad - lambda0_rad);
    double lambda_s = std::sin(lambda_rad - lambda0_rad);

    //(4) t, t_の計算
    double t = std::sinh(
        std::atanh(std::sin(phi_rad))-
        ((2*std::sqrt(n))/(1+n))*
        std::atanh(((2*std::sqrt(n))/(1+n))*std::sin(phi_rad))
        );
    double t_ = std::sqrt(1+t*t);

    //(5) xi', eta'の計算
    double xi2  = std::atan2(t / lambda_c); //[rad]
    double eta2 = std::atanh(lambda_s / t_);

    //(6)x, yの計算(chatGPTくんに助けてもらった)
    std::vector<int> indices = {1, 2, 3, 4, 5};
    std::vector<double> alpha_array_5 = alpha_array_6;//コピー
    alpha_array_5.erase(alpha_array_5.begin());//始めの要素を消す(これで要素5つに)
    // sum(alpha_array[1:] * (std::sin(2*xi2*n) * cosh(2*eta2*n)))
    double sum_x = std::inner_product(indices.begin(), indices.end(),
alpha_array_5.begin() + 1, 0.0, std::plus<>(),
        [&](int n, double alpha) {
            return alpha * std::sin(2 * xi2 * n) * std::cosh(2 * eta2 * n);
        }
    );

    // sum(alpha_array[1:] * (std::cos(2*xi2*n) * std::sinh(2*eta2*n)))
    double sum_y = std::inner_product(indices.begin(), indices.end(),
alpha_array_5.begin() + 1, 0.0, std::plus<>(),
        [&](int n, double alpha) {
            return alpha * std::cos(2 * xi2 * n) * std::sinh(2 * eta2 * n);
        }
    );

    // x, y の計算
    double x = A_ * (xi2 + sum_x) - S_; // [m]
    double y = A_ * (eta2 + sum_y);     // [m]

    return{x,y};
}
*/