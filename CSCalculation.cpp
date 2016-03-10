//
// Created by Caglar Sinayuc on 11/02/16.
//

#include "CSCalculation.h"

#include <ctime>
#include "voro++.hh"
#include "CSSolver.h"
#include <math.h>
using namespace voro;

#include <vector>
using namespace std;

// Set up constants for the container geometry
const double x_min=0,x_max=6000;
const double y_min=0,y_max=6000;
const double z_min=0,z_max=80;
const double cvol=(x_max-x_min)*(y_max-y_min)*(z_max-z_min);

// Set up the number of blocks that the container is divided into
const int n_x=60,n_y=60,n_z=6;

// The sampling distance for the grids of find_voronoi_cell calls
//const double h=0.05;

// The cube of the sampling distance, corresponding the amount of volume
// associated with a sample point
//const double hcube=h*h*h;

// Set the number of particles that are going to be randomly introduced
const int particles=25;
//const int particles=498;


// This function returns a random double between 0 and 1
double rnd() {
    return double(rand())/RAND_MAX;
}

//container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,false,false,false,8);


void Calculation::calculate() {


    int i;
    double x,y,z,r;
    vector<int> neigh, f_vert;
    vector<double> vec, faceAreas;
    srand( (unsigned)time( NULL ) );

    unsigned long maxNumberOfNeighbors = 0; // henuz bir yerde kullanmadim belki lazim olur

    container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,false,false,false,8);



    //random olarak dagitmak icin
    /*
    for(i=0;i<particles-1;i++) {
        x=x_min+rnd()*(x_max-x_min);
        y=y_min+rnd()*(y_max-y_min);
        z=40;
        con.put(i,x,y,z);
    }
     */



    /*
    con.put(0, 8.02959, 3857.21, 40);
    con.put(1, 41.0227, 4044.32, 40);
    con.put(2, 74.0159, 4231.43, 40);
    con.put(3, 107.009, 4418.55, 40);
    con.put(4, 140.002, 4605.66, 40);
    con.put(5, 172.995, 4792.77, 40);
    con.put(6, 205.989, 4979.89, 40);
    con.put(7, 238.982, 5167, 40);
    con.put(8, 271.975, 5354.11, 40);
    con.put(9, 304.968, 5541.23, 40);
    con.put(10, 337.961, 5728.34, 40);
    con.put(11, 370.954, 5915.45, 40);
    con.put(12, 19.3318, 1732.97, 40);
    con.put(13, 52.325, 1920.08, 40);
    con.put(14, 85.3182, 2107.2, 40);
    con.put(15, 118.311, 2294.31, 40);
    con.put(16, 151.304, 2481.42, 40);
    con.put(17, 184.298, 2668.54, 40);
    con.put(18, 217.291, 2855.65, 40);
    con.put(19, 250.284, 3042.77, 40);
    con.put(20, 283.277, 3229.88, 40);
    con.put(21, 316.27, 3416.99, 40);
    con.put(22, 349.263, 3604.11, 40);
    con.put(23, 382.257, 3791.22, 40);
    con.put(24, 415.25, 3978.33, 40);
    con.put(25, 448.243, 4165.45, 40);
    con.put(26, 481.236, 4352.56, 40);
    con.put(27, 514.229, 4539.67, 40);
    con.put(28, 547.222, 4726.79, 40);
    con.put(29, 580.215, 4913.9, 40);
    con.put(30, 613.209, 5101.01, 40);
    con.put(31, 646.202, 5288.13, 40);
    con.put(32, 679.195, 5475.24, 40);
    con.put(33, 712.188, 5662.35, 40);
    con.put(34, 745.181, 5849.47, 40);
    con.put(35, 129.614, 170.077, 40);
    con.put(36, 162.607, 357.19, 40);
    con.put(37, 195.6, 544.304, 40);
    con.put(38, 228.593, 731.417, 40);
    con.put(39, 261.586, 918.531, 40);
    con.put(40, 294.579, 1105.64, 40);
    con.put(41, 327.572, 1292.76, 40);
    con.put(42, 360.566, 1479.87, 40);
    con.put(43, 393.559, 1666.98, 40);
    con.put(44, 426.552, 1854.1, 40);
    con.put(45, 459.545, 2041.21, 40);
    con.put(46, 492.538, 2228.32, 40);
    con.put(47, 525.531, 2415.44, 40);
    con.put(48, 558.525, 2602.55, 40);
    con.put(49, 591.518, 2789.67, 40);
    con.put(50, 624.511, 2976.78, 40);
    con.put(51, 657.504, 3163.89, 40);
    con.put(52, 690.497, 3351.01, 40);
    con.put(53, 723.49, 3538.12, 40);
    con.put(54, 756.483, 3725.23, 40);
    con.put(55, 789.477, 3912.35, 40);
    con.put(56, 822.47, 4099.46, 40);
    con.put(57, 855.463, 4286.57, 40);
    con.put(58, 888.456, 4473.69, 40);
    con.put(59, 921.449, 4660.8, 40);
    con.put(60, 954.442, 4847.91, 40);
    con.put(61, 987.436, 5035.03, 40);
    con.put(62, 1020.43, 5222.14, 40);
    con.put(63, 1053.42, 5409.25, 40);
    con.put(64, 1086.42, 5596.37, 40);
    con.put(65, 1119.41, 5783.48, 40);
    con.put(66, 1152.4, 5970.59, 40);
    con.put(67, 503.841, 104.09, 40);
    con.put(68, 536.834, 291.204, 40);
    con.put(69, 569.827, 478.317, 40);
    con.put(70, 602.82, 665.431, 40);
    con.put(71, 635.813, 852.544, 40);
    con.put(72, 668.806, 1039.66, 40);
    con.put(73, 701.799, 1226.77, 40);
    con.put(74, 734.793, 1413.88, 40);
    con.put(75, 767.786, 1601, 40);
    con.put(76, 800.779, 1788.11, 40);
    con.put(77, 833.772, 1975.23, 40);
    con.put(78, 866.765, 2162.34, 40);
    con.put(79, 899.758, 2349.45, 40);
    con.put(80, 932.752, 2536.57, 40);
    con.put(81, 965.745, 2723.68, 40);
    con.put(82, 998.738, 2910.79, 40);
    con.put(83, 1031.73, 3097.91, 40);
    con.put(84, 1064.72, 3285.02, 40);
    con.put(85, 1097.72, 3472.13, 40);
    con.put(86, 1130.71, 3659.25, 40);
    con.put(87, 1163.7, 3846.36, 40);
    con.put(88, 1196.7, 4033.47, 40);
    con.put(89, 1229.69, 4220.59, 40);
    con.put(90, 1262.68, 4407.7, 40);
    con.put(91, 1295.68, 4594.81, 40);
    con.put(92, 1328.67, 4781.93, 40);
    con.put(93, 1361.66, 4969.04, 40);
    con.put(94, 1394.66, 5156.15, 40);
    con.put(95, 1427.65, 5343.27, 40);
    con.put(96, 1460.64, 5530.38, 40);
    con.put(97, 1493.64, 5717.49, 40);
    con.put(98, 1526.63, 5904.61, 40);
    con.put(99, 878.067, 38.1041, 40);
    con.put(100, 911.061, 225.218, 40);
    con.put(101, 944.054, 412.331, 40);
    con.put(102, 977.047, 599.444, 40);
    con.put(103, 1010.04, 786.558, 40);
    con.put(104, 1043.03, 973.671, 40);
    con.put(105, 1076.03, 1160.78, 40);
    con.put(106, 1109.02, 1347.9, 40);
    con.put(107, 1142.01, 1535.01, 40);
    con.put(108, 1175.01, 1722.13, 40);
    con.put(109, 1208, 1909.24, 40);
    con.put(110, 1240.99, 2096.35, 40);
    con.put(111, 1273.99, 2283.47, 40);
    con.put(112, 1306.98, 2470.58, 40);
    con.put(113, 1339.97, 2657.69, 40);
    con.put(114, 1372.96, 2844.81, 40);
    con.put(115, 1405.96, 3031.92, 40);
    con.put(116, 1438.95, 3219.03, 40);
    con.put(117, 1471.94, 3406.15, 40);
    con.put(118, 1504.94, 3593.26, 40);
    con.put(119, 1537.93, 3780.37, 40);
    con.put(120, 1570.92, 3967.49, 40);
    con.put(121, 1603.92, 4154.6, 40);
    con.put(122, 1636.91, 4341.71, 40);
    con.put(123, 1669.9, 4528.83, 40);
    con.put(124, 1702.9, 4715.94, 40);
    con.put(125, 1735.89, 4903.05, 40);
    con.put(126, 1768.88, 5090.17, 40);
    con.put(127, 1801.88, 5277.28, 40);
    con.put(128, 1834.87, 5464.39, 40);
    con.put(129, 1867.86, 5651.51, 40);
    con.put(130, 1900.86, 5838.62, 40);
    con.put(131, 1285.29, 159.231, 40);
    con.put(132, 1318.28, 346.345, 40);
    con.put(133, 1351.27, 533.458, 40);
    con.put(134, 1384.27, 720.572, 40);
    con.put(135, 1417.26, 907.685, 40);
    con.put(136, 1450.25, 1094.8, 40);
    con.put(137, 1483.25, 1281.91, 40);
    con.put(138, 1516.24, 1469.03, 40);
    con.put(139, 1549.23, 1656.14, 40);
    con.put(140, 1582.23, 1843.25, 40);
    con.put(141, 1615.22, 2030.37, 40);
    con.put(142, 1648.21, 2217.48, 40);
    con.put(143, 1681.21, 2404.59, 40);
    con.put(144, 1714.2, 2591.71, 40);
    con.put(145, 1747.19, 2778.82, 40);
    con.put(146, 1780.18, 2965.93, 40);
    con.put(147, 1813.18, 3153.05, 40);
    con.put(148, 1846.17, 3340.16, 40);
    con.put(149, 1879.16, 3527.27, 40);
    con.put(150, 1912.16, 3714.39, 40);
    con.put(151, 1945.15, 3901.5, 40);
    con.put(152, 1978.14, 4088.61, 40);
    con.put(153, 2011.14, 4275.73, 40);
    con.put(154, 2044.13, 4462.84, 40);
    con.put(155, 2077.12, 4649.95, 40);
    con.put(156, 2110.12, 4837.07, 40);
    con.put(157, 2143.11, 5024.18, 40);
    con.put(158, 2176.1, 5211.3, 40);
    con.put(159, 2209.1, 5398.41, 40);
    con.put(160, 2242.09, 5585.52, 40);
    con.put(161, 2275.08, 5772.64, 40);
    con.put(162, 2308.08, 5959.75, 40);
    con.put(163, 1659.51, 93.2449, 40);
    con.put(164, 1692.51, 280.358, 40);
    con.put(165, 1725.5, 467.472, 40);
    con.put(166, 1758.49, 654.585, 40);
    con.put(167, 1791.49, 841.699, 40);
    con.put(168, 1824.48, 1028.81, 40);
    con.put(169, 1857.47, 1215.93, 40);
    con.put(170, 1890.47, 1403.04, 40);
    con.put(171, 1923.46, 1590.15, 40);
    con.put(172, 1956.45, 1777.27, 40);
    con.put(173, 1989.45, 1964.38, 40);
    con.put(174, 2022.44, 2151.49, 40);
    con.put(175, 2055.43, 2338.61, 40);
    con.put(176, 2088.43, 2525.72, 40);
    con.put(177, 2121.42, 2712.83, 40);
    con.put(178, 2154.41, 2899.95, 40);
    con.put(179, 2187.4, 3087.06, 40);
    con.put(180, 2220.4, 3274.17, 40);
    con.put(181, 2253.39, 3461.29, 40);
    con.put(182, 2286.38, 3648.4, 40);
    con.put(183, 2319.38, 3835.51, 40);
    con.put(184, 2352.37, 4022.63, 40);
    con.put(185, 2385.36, 4209.74, 40);
    con.put(186, 2418.36, 4396.85, 40);
    con.put(187, 2451.35, 4583.97, 40);
    con.put(188, 2484.34, 4771.08, 40);
    con.put(189, 2517.34, 4958.2, 40);
    con.put(190, 2550.33, 5145.31, 40);
    con.put(191, 2583.32, 5332.42, 40);
    con.put(192, 2616.32, 5519.54, 40);
    con.put(193, 2649.31, 5706.65, 40);
    con.put(194, 2682.3, 5893.76, 40);
    con.put(195, 2033.74, 27.2586, 40);
    con.put(196, 2066.73, 214.372, 40);
    con.put(197, 2099.73, 401.486, 40);
    con.put(198, 2132.72, 588.599, 40);
    con.put(199, 2165.71, 775.713, 40);
    con.put(200, 2198.71, 962.826, 40);
    con.put(201, 2231.7, 1149.94, 40);
    con.put(202, 2264.69, 1337.05, 40);
    con.put(203, 2297.69, 1524.17, 40);
    con.put(204, 2330.68, 1711.28, 40);
    con.put(205, 2363.67, 1898.39, 40);
    con.put(206, 2396.67, 2085.51, 40);
    con.put(207, 2429.66, 2272.62, 40);
    con.put(208, 2462.65, 2459.73, 40);
    con.put(209, 2495.65, 2646.85, 40);
    con.put(210, 2528.64, 2833.96, 40);
    con.put(211, 2561.63, 3021.07, 40);
    con.put(212, 2594.63, 3208.19, 40);
    con.put(213, 2627.62, 3395.3, 40);
    con.put(214, 2660.61, 3582.41, 40);
    con.put(215, 2693.6, 3769.53, 40);
    con.put(216, 2726.6, 3956.64, 40);
    con.put(217, 2759.59, 4143.76, 40);
    con.put(218, 2792.58, 4330.87, 40);
    con.put(219, 2825.58, 4517.98, 40);
    con.put(220, 2858.57, 4705.1, 40);
    con.put(221, 2891.56, 4892.21, 40);
    con.put(222, 2924.56, 5079.32, 40);
    con.put(223, 2957.55, 5266.44, 40);
    con.put(224, 2990.54, 5453.55, 40);
    con.put(225, 3023.54, 5640.66, 40);
    con.put(226, 3056.53, 5827.78, 40);
    con.put(227, 2440.96, 148.386, 40);
    con.put(228, 2473.95, 335.499, 40);
    con.put(229, 2506.95, 522.613, 40);
    con.put(230, 2539.94, 709.726, 40);
    con.put(231, 2572.93, 896.84, 40);
    con.put(232, 2605.93, 1083.95, 40);
    con.put(233, 2638.92, 1271.07, 40);
    con.put(234, 2671.91, 1458.18, 40);
    con.put(235, 2704.91, 1645.29, 40);
    con.put(236, 2737.9, 1832.41, 40);
    con.put(237, 2770.89, 2019.52, 40);
    con.put(238, 2803.89, 2206.63, 40);
    con.put(239, 2836.88, 2393.75, 40);
    con.put(240, 2869.87, 2580.86, 40);
    con.put(241, 2902.87, 2767.97, 40);
    con.put(242, 2935.86, 2955.09, 40);
    con.put(243, 2968.85, 3142.2, 40);
    con.put(244, 3001.85, 3329.31, 40);
    con.put(245, 3034.84, 3516.43, 40);
    con.put(246, 3067.83, 3703.54, 40);
    con.put(247, 3100.82, 3890.66, 40);
    con.put(248, 3133.82, 4077.77, 40);
    con.put(249, 3166.81, 4264.88, 40);
    con.put(250, 3199.8, 4452, 40);
    con.put(251, 3232.8, 4639.11, 40);
    con.put(252, 3265.79, 4826.22, 40);
    con.put(253, 3298.78, 5013.34, 40);
    con.put(254, 3331.78, 5200.45, 40);
    con.put(255, 3364.77, 5387.56, 40);
    con.put(256, 3397.76, 5574.68, 40);
    con.put(257, 3430.76, 5761.79, 40);
    con.put(258, 3463.75, 5948.9, 40);
    con.put(259, 2815.19, 82.3995, 40);
    con.put(260, 2848.18, 269.513, 40);
    con.put(261, 2881.17, 456.626, 40);
    con.put(262, 2914.17, 643.74, 40);
    con.put(263, 2947.16, 830.853, 40);
    con.put(264, 2980.15, 1017.97, 40);
    con.put(265, 3013.15, 1205.08, 40);
    con.put(266, 3046.14, 1392.19, 40);
    con.put(267, 3079.13, 1579.31, 40);
    con.put(268, 3112.13, 1766.42, 40);
    con.put(269, 3145.12, 1953.53, 40);
    con.put(270, 3178.11, 2140.65, 40);
    con.put(271, 3211.11, 2327.76, 40);
    con.put(272, 3244.1, 2514.87, 40);
    con.put(273, 3277.09, 2701.99, 40);
    con.put(274, 3310.09, 2889.1, 40);
    con.put(275, 3343.08, 3076.22, 40);
    con.put(276, 3376.07, 3263.33, 40);
    con.put(277, 3409.07, 3450.44, 40);
    con.put(278, 3442.06, 3637.56, 40);
    con.put(279, 3475.05, 3824.67, 40);
    con.put(280, 3508.04, 4011.78, 40);
    con.put(281, 3541.04, 4198.9, 40);
    con.put(282, 3574.03, 4386.01, 40);
    con.put(283, 3607.02, 4573.12, 40);
    con.put(284, 3640.02, 4760.24, 40);
    con.put(285, 3673.01, 4947.35, 40);
    con.put(286, 3706, 5134.46, 40);
    con.put(287, 3739, 5321.58, 40);
    con.put(288, 3771.99, 5508.69, 40);
    con.put(289, 3804.98, 5695.8, 40);
    con.put(290, 3837.98, 5882.92, 40);
    con.put(291, 3189.42, 16.4132, 40);
    con.put(292, 3222.41, 203.527, 40);
    con.put(293, 3255.4, 390.64, 40);
    con.put(294, 3288.39, 577.754, 40);
    con.put(295, 3321.39, 764.867, 40);
    con.put(296, 3354.38, 951.981, 40);
    con.put(297, 3387.37, 1139.09, 40);
    con.put(298, 3420.37, 1326.21, 40);
    con.put(299, 3453.36, 1513.32, 40);
    con.put(300, 3486.35, 1700.43, 40);
    con.put(301, 3519.35, 1887.55, 40);
    con.put(302, 3552.34, 2074.66, 40);
    con.put(303, 3585.33, 2261.77, 40);
    con.put(304, 3618.33, 2448.89, 40);
    con.put(305, 3651.32, 2636, 40);
    con.put(306, 3684.31, 2823.12, 40);
    con.put(307, 3717.31, 3010.23, 40);
    con.put(308, 3750.3, 3197.34, 40);
    con.put(309, 3783.29, 3384.46, 40);
    con.put(310, 3816.29, 3571.57, 40);
    con.put(311, 3849.28, 3758.68, 40);
    con.put(312, 3882.27, 3945.8, 40);
    con.put(313, 3915.26, 4132.91, 40);
    con.put(314, 3948.26, 4320.02, 40);
    con.put(315, 3981.25, 4507.14, 40);
    con.put(316, 4014.24, 4694.25, 40);
    con.put(317, 4047.24, 4881.36, 40);
    con.put(318, 4080.23, 5068.48, 40);
    con.put(319, 4113.22, 5255.59, 40);
    con.put(320, 4146.22, 5442.7, 40);
    con.put(321, 4179.21, 5629.82, 40);
    con.put(322, 4212.2, 5816.93, 40);
    con.put(323, 3596.64, 137.54, 40);
    con.put(324, 3629.63, 324.654, 40);
    con.put(325, 3662.62, 511.767, 40);
    con.put(326, 3695.62, 698.881, 40);
    con.put(327, 3728.61, 885.994, 40);
    con.put(328, 3761.6, 1073.11, 40);
    con.put(329, 3794.59, 1260.22, 40);
    con.put(330, 3827.59, 1447.33, 40);
    con.put(331, 3860.58, 1634.45, 40);
    con.put(332, 3893.57, 1821.56, 40);
    con.put(333, 3926.57, 2008.68, 40);
    con.put(334, 3959.56, 2195.79, 40);
    con.put(335, 3992.55, 2382.9, 40);
    con.put(336, 4025.55, 2570.02, 40);
    con.put(337, 4058.54, 2757.13, 40);
    con.put(338, 4091.53, 2944.24, 40);
    con.put(339, 4124.53, 3131.36, 40);
    con.put(340, 4157.52, 3318.47, 40);
    con.put(341, 4190.51, 3505.58, 40);
    con.put(342, 4223.51, 3692.7, 40);
    con.put(343, 4256.5, 3879.81, 40);
    con.put(344, 4289.49, 4066.92, 40);
    con.put(345, 4322.48, 4254.04, 40);
    con.put(346, 4355.48, 4441.15, 40);
    con.put(347, 4388.47, 4628.26, 40);
    con.put(348, 4421.46, 4815.38, 40);
    con.put(349, 4454.46, 5002.49, 40);
    con.put(350, 4487.45, 5189.6, 40);
    con.put(351, 4520.44, 5376.72, 40);
    con.put(352, 4553.44, 5563.83, 40);
    con.put(353, 4586.43, 5750.94, 40);
    con.put(354, 4619.42, 5938.06, 40);
    con.put(355, 3970.86, 71.554, 40);
    con.put(356, 4003.86, 258.668, 40);
    con.put(357, 4036.85, 445.781, 40);
    con.put(358, 4069.84, 632.894, 40);
    con.put(359, 4102.84, 820.008, 40);
    con.put(360, 4135.83, 1007.12, 40);
    con.put(361, 4168.82, 1194.23, 40);
    con.put(362, 4201.81, 1381.35, 40);
    con.put(363, 4234.81, 1568.46, 40);
    con.put(364, 4267.8, 1755.58, 40);
    con.put(365, 4300.79, 1942.69, 40);
    con.put(366, 4333.79, 2129.8, 40);
    con.put(367, 4366.78, 2316.92, 40);
    con.put(368, 4399.77, 2504.03, 40);
    con.put(369, 4432.77, 2691.14, 40);
    con.put(370, 4465.76, 2878.26, 40);
    con.put(371, 4498.75, 3065.37, 40);
    con.put(372, 4531.75, 3252.48, 40);
    con.put(373, 4564.74, 3439.6, 40);
    con.put(374, 4597.73, 3626.71, 40);
    con.put(375, 4630.73, 3813.82, 40);
    con.put(376, 4663.72, 4000.94, 40);
    con.put(377, 4696.71, 4188.05, 40);
    con.put(378, 4729.71, 4375.16, 40);
    con.put(379, 4762.7, 4562.28, 40);
    con.put(380, 4795.69, 4749.39, 40);
    con.put(381, 4828.68, 4936.5, 40);
    con.put(382, 4861.68, 5123.62, 40);
    con.put(383, 4894.67, 5310.73, 40);
    con.put(384, 4927.66, 5497.84, 40);
    con.put(385, 4960.66, 5684.96, 40);
    con.put(386, 4993.65, 5872.07, 40);
    con.put(387, 4345.09, 5.56772, 40);
    con.put(388, 4378.08, 192.681, 40);
    con.put(389, 4411.08, 379.795, 40);
    con.put(390, 4444.07, 566.908, 40);
    con.put(391, 4477.06, 754.022, 40);
    con.put(392, 4510.06, 941.135, 40);
    con.put(393, 4543.05, 1128.25, 40);
    con.put(394, 4576.04, 1315.36, 40);
    con.put(395, 4609.03, 1502.48, 40);
    con.put(396, 4642.03, 1689.59, 40);
    con.put(397, 4675.02, 1876.7, 40);
    con.put(398, 4708.01, 2063.82, 40);
    con.put(399, 4741.01, 2250.93, 40);
    con.put(400, 4774, 2438.04, 40);
    con.put(401, 4806.99, 2625.16, 40);
    con.put(402, 4839.99, 2812.27, 40);
    con.put(403, 4872.98, 2999.38, 40);
    con.put(404, 4905.97, 3186.5, 40);
    con.put(405, 4938.97, 3373.61, 40);
    con.put(406, 4971.96, 3560.72, 40);
    con.put(407, 5004.95, 3747.84, 40);
    con.put(408, 5037.95, 3934.95, 40);
    con.put(409, 5070.94, 4122.06, 40);
    con.put(410, 5103.93, 4309.18, 40);
    con.put(411, 5136.93, 4496.29, 40);
    con.put(412, 5169.92, 4683.4, 40);
    con.put(413, 5202.91, 4870.52, 40);
    con.put(414, 5235.9, 5057.63, 40);
    con.put(415, 5268.9, 5244.74, 40);
    con.put(416, 5301.89, 5431.86, 40);
    con.put(417, 5334.88, 5618.97, 40);
    con.put(418, 5367.88, 5806.09, 40);
    con.put(419, 5400.87, 5993.2, 40);
    con.put(420, 4752.31, 126.695, 40);
    con.put(421, 4785.3, 313.808, 40);
    con.put(422, 4818.3, 500.922, 40);
    con.put(423, 4851.29, 688.035, 40);
    con.put(424, 4884.28, 875.149, 40);
    con.put(425, 4917.28, 1062.26, 40);
    con.put(426, 4950.27, 1249.38, 40);
    con.put(427, 4983.26, 1436.49, 40);
    con.put(428, 5016.25, 1623.6, 40);
    con.put(429, 5049.25, 1810.72, 40);
    con.put(430, 5082.24, 1997.83, 40);
    con.put(431, 5115.23, 2184.94, 40);
    con.put(432, 5148.23, 2372.06, 40);
    con.put(433, 5181.22, 2559.17, 40);
    con.put(434, 5214.21, 2746.28, 40);
    con.put(435, 5247.21, 2933.4, 40);
    con.put(436, 5280.2, 3120.51, 40);
    con.put(437, 5313.19, 3307.62, 40);
    con.put(438, 5346.19, 3494.74, 40);
    con.put(439, 5379.18, 3681.85, 40);
    con.put(440, 5412.17, 3868.96, 40);
    con.put(441, 5445.17, 4056.08, 40);
    con.put(442, 5478.16, 4243.19, 40);
    con.put(443, 5511.15, 4430.3, 40);
    con.put(444, 5544.15, 4617.42, 40);
    con.put(445, 5577.14, 4804.53, 40);
    con.put(446, 5610.13, 4991.65, 40);
    con.put(447, 5643.12, 5178.76, 40);
    con.put(448, 5676.12, 5365.87, 40);
    con.put(449, 5709.11, 5552.99, 40);
    con.put(450, 5742.1, 5740.1, 40);
    con.put(451, 5775.1, 5927.21, 40);
    con.put(452, 5126.54, 60.7086, 40);
    con.put(453, 5159.53, 247.822, 40);
    con.put(454, 5192.52, 434.936, 40);
    con.put(455, 5225.52, 622.049, 40);
    con.put(456, 5258.51, 809.162, 40);
    con.put(457, 5291.5, 996.276, 40);
    con.put(458, 5324.5, 1183.39, 40);
    con.put(459, 5357.49, 1370.5, 40);
    con.put(460, 5390.48, 1557.62, 40);
    con.put(461, 5423.47, 1744.73, 40);
    con.put(462, 5456.47, 1931.84, 40);
    con.put(463, 5489.46, 2118.96, 40);
    con.put(464, 5522.45, 2306.07, 40);
    con.put(465, 5555.45, 2493.18, 40);
    con.put(466, 5588.44, 2680.3, 40);
    con.put(467, 5621.43, 2867.41, 40);
    con.put(468, 5654.43, 3054.52, 40);
    con.put(469, 5687.42, 3241.64, 40);
    con.put(470, 5720.41, 3428.75, 40);
    con.put(471, 5753.41, 3615.86, 40);
    con.put(472, 5786.4, 3802.98, 40);
    con.put(473, 5819.39, 3990.09, 40);
    con.put(474, 5852.39, 4177.2, 40);
    con.put(475, 5885.38, 4364.32, 40);
    con.put(476, 5918.37, 4551.43, 40);
    con.put(477, 5951.37, 4738.55, 40);
    con.put(478, 5984.36, 4925.66, 40);
    con.put(479, 5533.76, 181.836, 40);
    con.put(480, 5566.75, 368.949, 40);
    con.put(481, 5599.74, 556.063, 40);
    con.put(482, 5632.74, 743.176, 40);
    con.put(483, 5665.73, 930.29, 40);
    con.put(484, 5698.72, 1117.4, 40);
    con.put(485, 5731.72, 1304.52, 40);
    con.put(486, 5764.71, 1491.63, 40);
    con.put(487, 5797.7, 1678.74, 40);
    con.put(488, 5830.69, 1865.86, 40);
    con.put(489, 5863.69, 2052.97, 40);
    con.put(490, 5896.68, 2240.08, 40);
    con.put(491, 5929.67, 2427.2, 40);
    con.put(492, 5962.67, 2614.31, 40);
    con.put(493, 5995.66, 2801.42, 40);
    con.put(494, 5907.98, 115.849, 40);
    con.put(495, 5940.98, 302.963, 40);
    con.put(496, 5973.97, 490.076, 40);
    */


    con.put(0, 1000, 1000, 40.0);
    con.put(1, 1000, 2000, 40.0);
    con.put(2, 1000, 3000, 40.0);
    con.put(3, 1000, 4000, 40.0);
    con.put(4, 1000, 5000, 40.0);
    con.put(5, 2000, 1000, 40.0);
    con.put(6, 2000, 2000, 40.0);
    con.put(7, 2000, 3000, 40.0);
    con.put(8, 2000, 4000, 40.0);
    con.put(9, 2000, 5000, 40.0);
    con.put(10, 3000, 1000, 40.0);
    con.put(11, 3000, 2000, 40.0);
    //con.put(12, 3000, 3000, 40.0);
    con.put(12, 3000, 4000, 40.0);
    con.put(13, 3000, 5000, 40.0);
    con.put(14, 4000, 1000, 40.0);
    con.put(15, 4000, 2000, 40.0);
    con.put(16, 4000, 3000, 40.0);
    con.put(17, 4000, 4000, 40.0);
    con.put(18, 4000, 5000, 40.0);
    con.put(19, 5000, 1000, 40.0);
    con.put(20, 5000, 2000, 40.0);
    con.put(21, 5000, 3000, 40.0);
    con.put(22, 5000, 4000, 40.0);
    con.put(23, 5000, 5000, 40.0);


    con.put(particles-1, 3000, 3000, 40); // orta noktadaki kuyu
    //con.put(particles-1, 3500, 500, 37.5);



/*
    con.put(0, 1000, 1000, 40);
    con.put(1, 3000, 1000, 40);
    con.put(2, 5000, 1000, 40);
    con.put(3, 1000, 3000, 40);
    con.put(4, 5000, 5000, 40);
    con.put(5, 5000, 3000, 40);
    con.put(6, 1000, 5000, 40);
    con.put(7, 3000, 5000, 40);
    con.put(8, 3000, 3000, 40);

    con.put(9, 1000, 1000, 80);
    con.put(10, 3000, 1000, 80);
    con.put(11, 5000, 1000, 80);
    con.put(12, 1000, 3000, 80);
    con.put(13, 5000, 5000, 80);
    con.put(14, 5000, 3000, 80);
    con.put(15, 1000, 5000, 80);
    con.put(16, 3000, 5000, 80);
    con.put(17, 3000, 3000, 80);
*/


    /*
    con.put(0, 550, 1000, 40);
    con.put(1, 2300, 1200, 40);
    con.put(2, 5400, 1100, 40);
    con.put(3, 1200, 3500, 40);
    con.put(4, 2000, 3000, 40);
    con.put(5, 6300, 3200, 40);
    con.put(6, 1400, 5500, 40);
    con.put(7, 2500, 6000, 40);
    con.put(8, 6000, 6000, 40);
     */

    //int particles = 0;

    positionX = new double[particles];
    positionY = new double[particles];
    positionZ = new double[particles];

    //double positionX[particles];
    //double positionY[particles];
    //double positionZ[particles];
    for (int count = 0; count < particles; count++) {
        positionX[count]=0;
        positionY[count]=0;
        positionZ[count]=0;
    }

    //double cellVolume[particles];
    cellVolume = new double[particles];
    for (int counter=0; counter<particles; counter++) {
        cellVolume[counter] = 0;
    }

    // Sum up the volumes, and check that this matches the container volume
    double vvol=con.sum_cell_volumes();
    printf("Container volume : %g\n"
                   "Voronoi volume   : %g\n"
                   "Difference       : %g\n",cvol,vvol,vvol-cvol);

    FILE *f1=safe_fopen("find_voro_cell.vol","w");
    FILE *f2=safe_fopen("find_voro_cell_v.gnu","w");
    c_loop_all cla(con);
    voronoicell_neighbor v;
    if(cla.start()) do if (con.compute_cell(v,cla)) {


                // Get the position and ID information for the particle
                // currently being considered by the loop. Ignore the radius
                // information.
                cla.pos(i,x,y,z,r);

                positionX[i] = x;
                positionY[i] = y;
                positionZ[i] = z;
                cellVolume[i] = v.volume();


                v.neighbors(neigh);
                //printf("particle: %d, neighbors: %lu\n", i, neigh.size());
                //printf("neighbors: %d, %d, %d, %d, %d, %d\n", neigh[0], neigh[1], neigh[2], neigh[3], neigh[4], neigh[5]);

                // For each face, this routine outputs a bracketed sequence of numbers
                // containing a list of all the vertices that make up that face.
                v.face_vertices(f_vert);
                //printf("particle: %d, faces: %lu\n", i, f_vert.size());
                //printf("faces: %d, %d, %d, %d, %d, %d\n", f_vert[0], f_vert[1], f_vert[2], f_vert[3], f_vert[4], f_vert[5]);

                v.vertices(x,y,z,vec);
                //printf("particle: %d, x: %f, y: %f, z: %f, vertices: %lu\n", i, x, y, z, v.size());
                //printf("vertices: %f, %f, %f, %f, %f, %f\n", v[0], v[1], v[2], v[3], v[4], v[5]);
                //printf("number of vertices %d\n", c.p);

                //v.face_areas(faceAreas);

                if (neigh.size() > maxNumberOfNeighbors) maxNumberOfNeighbors = neigh.size();




                // Output the Voronoi cell to a file in gnuplot format
                v.draw_gnuplot(0,0,0,"simple_cell.gnu");

                printf("Cell ID             :%d\n", cla.pid());

                // Output vertex-based statistics
                printf("Total vertices      : %d\n",v.p);
                printf("Vertex positions    : ");v.output_vertices();puts("");
                printf("Vertex orders       : ");v.output_vertex_orders();puts("");
                printf("Max rad. sq. vertex : %g\n\n",0.25*v.max_radius_squared());

                // Output edge-based statistics
                printf("Total edges         : %d\n",v.number_of_edges());
                printf("Total edge distance : %g\n",v.total_edge_distance());
                printf("Face perimeters     : ");v.output_face_perimeters();puts("\n");

                // Output face-based statistics
                printf("Total faces         : %d\n",v.number_of_faces());
                printf("Surface area        : %g\n",v.surface_area());
                printf("Face freq. table    : ");v.output_face_freq_table();puts("");
                printf("Face orders         : ");v.output_face_orders();puts("");
                printf("Face areas          : ");v.output_face_areas();puts("");
                printf("Face normals        : ");v.output_normals();puts("");
                printf("Face vertices       : ");v.output_face_vertices();puts("");
                printf("Neighbors           : ");v.output_neighbors();puts("\n");

                // Output volume-based statistics
                v.centroid(x,y,z);
                printf("Volume              : %g\n"
                               "Centroid vector     : (%g,%g,%g)\n",v.volume(),x,y,z);




                // Draw the Voronoi cell
                v.draw_gnuplot(x,y,z,f2);
            } while (cla.inc());
    fclose(f1);
    fclose(f2);

    // Do a custom output routine to store the number of vertices, edges,
    // and faces of each Voronoi cell
    con.print_custom(
            "ID=%i, pos=(%x,%y,%z), vertices=%w, edges=%g, faces=%s",
            "random.custom1");

    // Do a custom output routine to store a variety of face-based
    // statistics. Store the particle ID and position, the number of faces
    // the total face area, the order of each face, the areas of each face,
    // the vertices making up each face, and the neighboring particle (or
    // wall) corresponding to each face.
    con.print_custom("%i %q %s %F %a %f %t %l %n","random.custom2");

    // Do a custom output routine that outputs the particle IDs and
    // positions, plus the volume and the centroid position relative to the
    // particle center
    con.print_custom("%i %q %v %c","random.custom3");

    // Also create POV-Ray output of the Voronoi cells for use in the
    // rendering
    con.draw_cells_pov("random_v.pov");

    // Output the particle positions in gnuplot format
    con.draw_particles("random_points_p.gnu");

    // Output the Voronoi cells in gnuplot format
    con.draw_cells_gnuplot("random_points_v.gnu");








    printf("number of particles: %d\n", particles);


    simRun(con);











}

double Calculation::distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow((x2-x1),2) + pow((y2-y1),2) + pow((z2-z1),2));
}

void Calculation::simRun(container& aCon) {

    double permeability = 0.015;
    double viscosity = 10;
    double formationVolumeFactor = 1;
    double porosity = 0.18;
    double liquidCompressibility = 3.5E-6;
    double referansFormationVolumeFactor = 1;
    double alphaConstant = 5.615;
    double betaConstant = 1.127;
    double deltaTime = 15;
    double length = 0;
    double totalCoefficient = 0;

    int numberOfTimeSteps = 10;

    int i;
    double x,y,z,r;
    vector<int> neigh, f_vert;
    vector<double> vec, faceAreas;
    double productionRate[particles];
    for (int counter=0; counter<particles; counter++) {
        productionRate[counter] = 0;
    }
    // lets say we have a well producing at 150 stb/day from the last particle
    productionRate[particles-1] = -150;

    double gamma[particles];
    for (int counter=0; counter<particles; counter++) {
        gamma[counter] = 0;
    }

    double pressure[particles];
    //pressure = new double [particles];
    for (int counter=0; counter<particles; counter++) {
        pressure[counter]=6000;
    }



    double rightHandSide[particles];
    //rightHandSide = new double[particles];
    for (int counter=0; counter<particles; counter++) {
        rightHandSide[counter] = 0;
    }


    coefficient = new double *[particles];
    for(int i = 0; i <particles; i++)
        coefficient[i] = new double[particles];

    for (int counter1=0; counter1<particles; counter1++) {
        for (int counter2=0; counter2<particles; counter2++) {
            coefficient[counter1][counter2]=0.0;
        }
    }

    Solution mySimpleSolver;
    double *solutionArray;
    solutionArray = new double[particles];
    for (int counter=0; counter<particles; counter++) {
        solutionArray[counter] = 0.0;
    }

    FILE *f3=safe_fopen("matrixA.dat","w");
    FILE *f4=safe_fopen("matrixB.dat","w");
    FILE *f5=safe_fopen("matrixSolution.dat","w");
    FILE *f6=safe_fopen("datafile.dat","w");

    for(int timeSteps = 0; timeSteps < numberOfTimeSteps; timeSteps++) {


        c_loop_all myLoop(aCon);
        voronoicell_neighbor myCell;
        if(myLoop.start()) do if (aCon.compute_cell(myCell,myLoop)) {
                    myLoop.pos(i,x,y,z,r);
                    myCell.neighbors(neigh);
                    myCell.face_areas(faceAreas);
                    totalCoefficient = 0;


                    printf("Particle: %d position: x: %f, y: %f, z: %f\n", i, x, y, z);
                    printf("Particle: %d position: x: %f, y: %f, z: %f, volume: %f\n", i, positionX[i], positionY[i], positionZ[i], myCell.volume());
                    for (int neighCounter = 0; neighCounter < neigh.size(); neighCounter++) {
                        printf("Particle %d neighbor %d = %d face area = %f\n", myLoop.pid(), neighCounter, neigh[neighCounter], faceAreas[neighCounter]);

                        if (neigh[neighCounter]>=0) {
                            length = distance(positionX[i], positionY[i], positionZ[i], positionX[neigh[neighCounter]], positionY[neigh[neighCounter]], positionZ[neigh[neighCounter]]);
                            coefficient[i][neigh[neighCounter]]=betaConstant*faceAreas[neighCounter]*permeability/(viscosity*formationVolumeFactor*length);
                            totalCoefficient = totalCoefficient + coefficient[i][neigh[neighCounter]];
                            printf("Neigbor: %d position: x: %f, y: %f, distance: %f\n",neigh[neighCounter], positionX[neigh[neighCounter]], positionY[neigh[neighCounter]], length);
                        }

                    }

                    printf("totalCoefficient = %f\n", totalCoefficient);
                    gamma[i] = (cellVolume[i]*porosity*liquidCompressibility)/(alphaConstant*referansFormationVolumeFactor);
                    coefficient[i][i] = -totalCoefficient-gamma[i]/deltaTime;

                    rightHandSide[i] = -productionRate[i] - (gamma[i]/deltaTime)*pressure[i];
                    printf("The i value is: %d and coefficient: %f productionRate:%f gamma:%f pressure:%f rightHandSide: %f\n", i, coefficient[i][i], productionRate[i], gamma[i], pressure[i], rightHandSide[i]);


                } while (myLoop.inc());



        for (int counter1=0; counter1<particles; counter1++) {
            //for (int counter2=0; counter2<particles; counter2++) {
            fprintf(f3, "%f %f %f %f %f \n",coefficient[counter1][0], coefficient[counter1][1], coefficient[counter1][2], coefficient[counter1][3], coefficient[counter1][4]);
            //}
        }


        for (int counter1=0; counter1<particles; counter1++) {
            fprintf(f4, "%f\n", rightHandSide[counter1]);
        }



        solutionArray = mySimpleSolver.simpleSolver(particles, coefficient, rightHandSide, pressure);

        for (int counter1=0; counter1<particles; counter1++) {
            pressure[counter1] = solutionArray[counter1];
        }

        fprintf(f5, "\nTime step: %d Day: %.f\n\n", timeSteps+1, (timeSteps+1)*deltaTime);
        fprintf(f6, "\nTime step: %d Day: %.f\n\n", timeSteps+1, (timeSteps+1)*deltaTime);

        for (int counter1=0; counter1<particles; counter1++) {
            fprintf(f5, "%f\n", solutionArray[counter1]);
        }

        for (int counter1=0; counter1<particles; counter1++) {
            fprintf(f6, "%f %f %f\n", positionX[counter1], positionY[counter1], solutionArray[counter1]);
        }

    } // for timeSteps

    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);


}
