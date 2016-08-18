#include <math.h>
#include <stdio.h>

// Constants
double t_policy_year_150 = 4000;
double t_air_poll_time = 4000;
double t_fcaor_time = 4000;
double t_fert_cont_eff_time_45 = 4000;
double t_ind_equil_time_57 = 4000;
double t_land_life_time = 4000;
double t_pop_equil_time_30 = 4000;
double t_zero_pop_grow_time_38 = 4000;
double urb_ind_land_dev_time_119 = 10;
double p_avg_life_agr_inp_1_100 = 2;
double p_avg_life_agr_inp_2_100 = 2;
double p_avg_life_ind_cap_1_54 = 14;
double p_avg_life_ind_cap_2_54 = 14;
double p_avg_life_serv_cap_1_69 = 20;
double p_avg_life_serv_cap_2_69 = 20;
double p_fioa_cons_const_1_58 = 0.43;
double p_fioa_cons_const_2_58 = 0.43;
double social_discount_109 = 0.07;
double p_land_yield_fact_1_104 = 1;
double des_food_ratio_DFR = 2;
double subsist_food_pc_127 = 230;
double labor_util_fr_del_time_82 = 2;
double life_expect_norm_19 = 28;
double processing_loss_87 = 0.1;
double land_fr_harvested_87 = 0.7;
double ppoll_in_1970_143 = 1.36e8;
double tech_dev_del_TDD = 20;
double hlth_serv_impact_del_22 = 20;
double p_serv_cap_out_ratio_1_72 = 1;
double p_serv_cap_out_ratio_2_72 = 1;
double reproductive_lifetime_30 = 30;
double max_tot_fert_norm_33 = 12;
double des_compl_fam_size_norm_38 = 3.8;
double social_adj_del_40 = 20;
double income_expect_avg_time_43 = 3;
double pot_arable_land_tot_84 = 3.2e9;
double p_ind_cap_out_ratio_1_51 = 3;
double p_nr_res_use_fact_1_131 = 1;
double des_ppoll_index_DPOLX = 1.2;
double des_res_use_rt_DNRUR = 4.8e9;
double ind_mtl_emiss_fact_139 = .1;
double ind_mtl_toxic_index_139 = 10;
double ind_out_in_1970_107 = 7.9e11;
double p_ppoll_gen_fact_1_138 = 1;
double labor_force_partic_80 = 0.75;
double ind_out_pc_des_59 = 400;
double inherent_land_fert_124 = 600;
double lifet_perc_del_37 = 20;
double avg_life_land_norm_112 = 1000;
double food_short_perc_del_128 = 2;
double frac_res_pers_mtl_139 = 0.02;
double fr_agr_inp_pers_mtl_140 = 0.001;
double agr_mtl_toxic_index_140 = 1;
double ppoll_trans_del_141 = 20;
double assim_half_life_1970_146 = 1.5;

// Graphs

typedef struct {
        double x, y;
} point_t;

typedef struct {
        int n;
        point_t points[];
} graph_t;

double graph_value_at(graph_t* graph, double x)
{
        if (x < graph->points[0].x) {
                return graph->points[0].y;
        }
        for (int i = 0; i < graph->n - 1; i++) {
                if ((x >= graph->points[i].x)
                    && (x < graph->points[i+1].x)) {
                        return graph->points[i].y 
                                + ((graph->points[i+1].y - graph->points[i].y) 
                                   * (x - graph->points[i].x) 
                                   / (graph->points[i+1].x - graph->points[i].x));
                }
        }
        return graph->points[graph->n - 1].y;
}
 
graph_t p_fr_io_al_agr_2_95_graph = { 6, {{0.00, 0.4}, {0.5, 0.2}, 
                                          {1.00, 0.1}, {1.50, 0.025}, 
                                          {2.00, 0.00}, {2.50, 0.00}}};

graph_t p_fr_io_al_agr_1_94_graph = { 6, {{0.00, 0.4}, {0.5, 0.2}, 
                                          {1.00, 0.1}, {1.50, 0.025}, 
                                          {2.00, 0.00}, {2.50, 0.00}}};

graph_t p_fr_io_al_serv_1_64_graph = { 5, {{0.00, 0.3}, {0.5, 0.2}, 
                                           {1.00, 0.1}, {1.50, 0.05}, 
                                           {2.00, 0.00}}};

graph_t p_fr_io_al_serv_2_65_graph = { 5, {{0.00, 0.3}, {0.5, 0.2}, 
                                           {1.00, 0.1}, {1.50, 0.05}, 
                                           {2.00, 0.00}}};

graph_t p_indic_food_pc_1_90_graph = { 9, {{0.00, 230}, {200, 480}, 
                                           {400, 690}, {600, 850}, 
                                           {800, 970}, {1000, 1070}, 
                                           {1200, 1150}, {1400, 1210}, 
                                           {1600, 1250}}};

graph_t p_indic_food_pc_2_91_graph = { 9, {{0.00, 230}, {200, 480}, 
                                           {400, 690}, {600, 850}, 
                                           {800, 970}, {1000, 1070}, 
                                           {1200, 1150}, {1400, 1210}, 
                                           {1600, 1250}}};

graph_t fr_inp_al_land_dev_108_graph = { 9, {{0.00, 0.00}, {0.25, 0.05}, 
                                             {0.5, 0.15}, {0.75, 0.3}, 
                                             {1.00, 0.5}, {1.25, 0.7}, 
                                             {1.50, 0.85}, {1.75, 0.95}, 
                                             {2.00, 1.00}}};

graph_t dev_cost_per_hect_97_graph = { 11, {{0.00, 100000}, {0.1, 7400}, 
                                            {0.2, 5200}, {0.3, 3500}, 
                                            {0.4, 2400}, {0.5, 1500}, 
                                            {0.6, 750}, {0.7, 300}, 
                                            {0.8, 150}, {0.9, 75.0}, 
                                            {1.00, 50.0}}};

graph_t p_yield_tech_chg_mlt_LYCM_graph = { 2, {{0.00, 0.00}, {1.00, 0.00}}};

graph_t jobs_per_ind_cap_unit_75_graph = { 6, {{50.0, 0.00037}, {200, 0.00018}, 
                                               {350, 0.00012}, {500, 9e-005}, 
                                               {650, 7e-005}, {800, 6e-005}}};

graph_t mortal_0_to_14_4_graph = { 7, {{20.0, 0.0567}, {30.0, 0.0366}, 
                                       {40.0, 0.0243}, {50.0, 0.0155}, 
                                       {60.0, 0.0082}, {70.0, 0.0023}, 
                                       {80.0, 0.001}}};

graph_t mortal_15_to_44_8_graph = { 7, {{20.0, 0.0266}, {30.0, 0.0171}, 
                                        {40.0, 0.011}, {50.0, 0.0065}, 
                                        {60.0, 0.004}, {70.0, 0.0016}, 
                                        {80.0, 0.0008}}};

graph_t mortal_45_to_64_12_graph = { 7, {{20.0, 0.0562}, {30.0, 0.0373}, 
                                         {40.0, 0.0252}, {50.0, 0.0171}, 
                                         {60.0, 0.0118}, {70.0, 0.0083}, 
                                         {80.0, 0.006}}};

graph_t mortal_65_plus_16_graph = { 7, {{20.0, 0.13}, {30.0, 0.11}, 
                                        {40.0, 0.09}, {50.0, 0.07}, 
                                        {60.0, 0.06}, {70.0, 0.05}, 
                                        {80.0, 0.04}}};


graph_t lifet_mlt_food_20_graph = { 6,  {{0.00, 0.00}, {1.00, 1.00}, 
                                         {2.00, 1.43}, {3.00, 1.50}, 
                                         {4.00, 1.50}, {5.00, 1.50}}};

graph_t land_fert_degr_rt_122_graph = { 4, {{0.00, 0.00}, {10.0, 0.1}, 
                                            {20.0, 0.3}, {30.0, 0.5}}};

graph_t land_yield_mlt_cap_102_graph = { 26, {{0.00, 1.00}, {40.0, 3.00}, 
                                              {80.0, 4.50}, {120, 5.00}, 
                                              {160, 5.30}, {200, 5.60}, 
                                              {240, 5.90}, {280, 6.10}, 
                                              {320, 6.35}, {360, 6.60}, 
                                              {400, 6.90}, {440, 7.20}, 
                                              {480, 7.40}, {520, 7.60}, 
                                              {560, 7.80}, {600, 8.00}, 
                                              {640, 8.20}, {680, 8.40}, 
                                              {720, 8.60}, {760, 8.80}, 
                                              {800, 9.00}, {840, 9.20}, 
                                              {880, 9.40}, {920, 9.60}, 
                                              {960, 9.80}, {1000, 10.0}}};

graph_t p_fr_inp_for_land_maint_126_graph = { 5, {{0.00, 0.00}, {1.00, 0.04}, 
                                                  {2.00, 0.07}, {3.00, 0.09}, 
                                                  {4.00, 0.1}}};
graph_t lifet_mlt_hlth_serv_2_25_graph = { 6, {{0.00, 1.00}, {20.0, 1.50}, 
                                               {40.0, 1.90}, {60.0, 2.00}, 
                                               {80.0, 2.00}, {100, 2.00}}};

graph_t hlth_serv_al_pc_21_graph = { 9, {{0.00, 0.00}, {250, 20.0}, 
                                         {500, 50.0}, {750, 95.0}, 
                                         {1000, 140}, {1250, 175}, 
                                         {1500, 200}, {1750, 220}, 
                                         {2000, 230}}};

graph_t p_indic_serv_pc_2_62_graph = { 9, {{0.00, 40.0}, {200, 300}, 
                                           {400, 640}, {600, 1000}, 
                                           {800, 1220}, {1000, 1450}, 
                                           {1200, 1650}, {1400, 1800}, 
                                           {1600, 2000}}};

graph_t p_fr_cap_al_obt_res_2_136_graph = { 11, {{0.00, 1.00}, {0.1, 0.2}, 
                                                 {0.2, 0.1}, {0.3, 0.05}, 
                                                 {0.4, 0.05}, {0.5, 0.05}, 
                                                 {0.6, 0.05}, {0.7, 0.05}, 
                                                 {0.8, 0.05}, {0.9, 0.05}, 
                                                 {1.00, 0.05}}};

graph_t p_indic_serv_pc_1_61_graph = { 9, {{0.00, 40.0}, {200, 300}, 
                                           {400, 640}, {600, 1000}, 
                                           {800, 1220}, {1000, 1450}, 
                                           {1200, 1650}, {1400, 1800}, 
                                           {1600, 2000}}};

graph_t p_fr_cap_al_obt_res_1_135_graph = { 11, {{0.00, 1.00}, {0.1, 0.9}, 
                                                 {0.2, 0.7}, {0.3, 0.5}, 
                                                 {0.4, 0.2}, {0.5, 0.1}, 
                                                 {0.6, 0.05}, {0.7, 0.05}, 
                                                 {0.8, 0.05}, {0.9, 0.05}, 
                                                 {1.00, 0.05}}};

graph_t jobs_per_hect_79_graph = { 8, {{2.00, 2.00}, {6.00, 0.5}, 
                                       {10.0, 0.4}, {14.0, 0.3}, 
                                       {18.0, 0.27}, {22.0, 0.24}, 
                                       {26.0, 0.2}, {30.0, 0.2}}};

graph_t capacity_util_fr_83_graph = { 6, {{1.00, 1.00}, {3.00, 0.9}, 
                                          {5.00, 0.7}, {7.00, 0.3}, 
                                          {9.00, 0.1}, {11.0, 0.1}}};

graph_t fecundity_mult_34_graph = { 9, {{0.00, 0.00}, {10.0, 0.2}, 
                                        {20.0, 0.4}, {30.0, 0.6}, 
                                        {40.0, 0.7}, {50.0, 0.75}, 
                                        {60.0, 0.79}, {70.0, 0.84}, 
                                        {80.0, 0.87}}};

graph_t soc_fam_size_norm_39_graph = { 5, {{0.00, 1.25}, {200, 0.94}, 
                                           {400, 0.715}, {600, 0.59}, 
                                           {800, 0.5}}};

graph_t ind_cap_out_ratio_2_ICOR2T_graph = { 12, {{0.00, 3.75}, 
                                                  {0.1, 3.60}, {0.2, 3.47}, 
                                                  {0.3, 3.36}, {0.4, 3.25}, 
                                                  {0.5, 3.16}, {0.6, 3.10}, 
                                                  {0.7, 3.06}, {0.8, 3.02},
                                                  {0.9, 3.01}, {1.00, 3.00}}};

graph_t yield_tech_mult_icor_COYM_graph = { 6, {{1.00, 1.00}, {1.20, 1.05}, 
                                                {1.40, 1.12}, {1.60, 1.25}, 
                                                {1.80, 1.35}, {2.00, 1.50}}};

graph_t ppoll_tech_mult_icor_COPM_graph = { 11, {{0.00, 1.25}, {0.1, 1.20}, 
                                                 {0.2, 1.15}, {0.3, 1.11}, 
                                                 {0.4, 1.08}, {0.5, 1.05}, 
                                                 {0.6, 1.03}, {0.7, 1.02}, 
                                                 {0.8, 1.01}, {0.9, 1.00}, 
                                                 {1.00, 1.00}}};

graph_t p_yield_mlt_air_poll_2_107_graph = { 4, {{0.00, 1.00}, {10.0, 1.00}, 
                                                 {20.0, 0.98}, {30.0, 0.95}}};

graph_t p_yield_mlt_air_poll_1_106_graph = { 4, {{0.00, 1.00}, {10.0, 1.00}, 
                                                 {20.0, 0.7}, {30.0, 0.4}}};

graph_t jobs_per_serv_cap_unit_77_graph = { 6, {{50.0, 0.0011}, {200, 0.0006}, 
                                                {350, 0.00035}, {500, 0.0002}, 
                                                {650, 0.00015}, {800, 0.00015}}};

graph_t lifet_mlt_hlth_serv_1_24_graph = { 6, {{0.00, 1.00}, {20.0, 1.10}, 
                                               {40.0, 1.40}, {60.0, 1.60}, 
                                               {80.0, 1.70}, {100, 1.80}}};

graph_t lifet_mlt_ppoll_29_graph = { 11, {{0.00, 1.00}, {10.0, 0.99}, 
                                          {20.0, 0.97}, {30.0, 0.95}, 
                                          {40.0, 0.9}, {50.0, 0.85}, 
                                          {60.0, 0.75}, {70.0, 0.65}, 
                                          {80.0, 0.55}, {90.0, 0.4}, 
                                          {100, 0.2}}};

graph_t crowd_mult_ind_27_graph = { 9, {{0.00, 0.5}, {200, 0.05}, 
                                        {400, -0.1}, {600, -0.08}, 
                                        {800, -0.02}, {1000, 0.05}, 
                                        {1200, 0.1}, {1400, 0.15}, 
                                        {1600, 0.2}}};

graph_t fr_pop_urban_26_graph = { 9, {{0.00, 0.00}, {2e+009, 0.2}, 
                                      {4e+009, 0.4}, {6e+009, 0.5}, 
                                      {8e+009, 0.58}, {1e+010, 0.65}, 
                                      {1.2e+010, 0.72}, {1.4e+010, 0.78}, 
                                      {1.6e+010, 0.8}}};

graph_t p_fioa_cons_var_59_graph = { 11, {{0.00, 0.3}, {0.2, 0.32}, 
                                          {0.4, 0.34}, {0.6, 0.36}, 
                                          {0.8, 0.38}, {1.00, 0.43}, 
                                          {1.20, 0.73}, {1.40, 0.77}, 
                                          {1.60, 0.81}, {1.80, 0.82}, 
                                          {2.00, 0.83}}};

graph_t marg_land_yield_mlt_cap_111_graph = { 16, {{0.00, 0.075}, {40.0, 0.03}, 
                                                   {80.0, 0.015}, {120, 0.011}, 
                                                   {160, 0.009}, {200, 0.008}, 
                                                   {240, 0.007}, {280, 0.006}, 
                                                   {320, 0.005}, {360, 0.005}, 
                                                   {400, 0.005}, {440, 0.005}, 
                                                   {480, 0.005}, {520, 0.005}, 
                                                   {560, 0.005}, {600, 0.005}}};

graph_t fam_resp_to_soc_norm_41_graph = { 7, {{-0.2, 0.5}, {-0.1, 0.6}, 
                                              {0.00, 0.7}, {0.1, 0.85}, 
                                              {0.2, 1.00}}};

graph_t compl_mlt_perc_lifet_36_graph = {  9, {{0.00, 3.00}, {10.0, 2.10}, 
                                               {20.0, 1.60}, {30.0, 1.40}, 
                                               {40.0, 1.30}, {50.0, 1.20}, 
                                               {60.0, 1.10}, {70.0, 1.05}, 
                                               {80.0, 1.00}}};

graph_t fr_serv_al_fert_cont_48_graph = { 6, {{0.00, 0.00}, {2.00, 0.005}, 
                                              {4.00, 0.015}, {6.00, 0.025}, 
                                              {8.00, 0.03}, {10.0, 0.035}}};

graph_t fert_cont_eff_table_45_graph = { 7, {{0.00, 0.75}, {0.5, 0.85}, 
                                             {1.00, 0.9}, {1.50, 0.95}, 
                                             {2.00, 0.98}, {2.50, 0.99}, 
                                             {3.00, 1.00}}};

graph_t urb_ind_land_pc_117_graph = {  9, {{0.00, 0.005}, {200, 0.008}, 
                                           {400, 0.015}, {600, 0.025}, 
                                           {800, 0.04}, {1000, 0.055}, 
                                           {1200, 0.07}, {1400, 0.08}, 
                                           {1600, 0.09}}};

graph_t p_land_life_mlt_yield_1_114_graph = { 10, {{0.00, 1.20}, {1.00, 1.00}, 
                                                   {2.00, 0.63}, {3.00, 0.36}, 
                                                   {4.00, 0.16}, {5.00, 0.055}, 
                                                   {6.00, 0.04}, {7.00, 0.025}, 
                                                   {8.00, 0.015}, {9.00, 0.01}}};

graph_t p_land_life_mlt_yield_2_115_graph = { 10, {{0.00, 1.20}, {1.00, 1.00}, 
                                                   {2.00, 0.63}, {3.00, 0.36}, 
                                                   {4.00, 0.29}, {5.00, 0.26}, 
                                                   {6.00, 0.24}, {7.00, 0.22}, 
                                                   {8.00, 0.21}, {9.00, 0.2}}};

graph_t pc_res_use_mlt_132_graph = { 9, {{0.00, 0.00}, {200, 0.85}, 
                                         {400, 2.60}, {600, 3.40}, 
                                         {800, 3.80}, {1000, 4.10}, 
                                         {1200, 4.40}, {1400, 4.70}, 
                                         {1600, 5.00}}};

graph_t assim_half_life_mlt_145_graph = { 5, {{1.00, 1.00}, {251, 11.0}, 
                                              {501, 21.0}, {751, 31.0}, 
                                              {1001, 41.0}}};

graph_t land_fert_regen_time_125_graph = { 6, {{0.00, 20.0}, {0.02, 13.0}, 
                                               {0.04, 8.00}, {0.06, 4.00}, 
                                               {0.08, 2.00}, {0.1, 2.00}}};

graph_t p_res_tech_chg_mlt_NRCM_graph = { 2, {{-1.00, 0.00}, {0.00, 0.00}}};

graph_t p_ppoll_tech_chg_mlt_POLGFM_graph = { 2, {{-1.00, 0.00}, {0.00, 0.00}}};


// State variables

typedef struct {
        double init;
        double val;
} stock_t;


stock_t pop_0_to_14_2 = { 65e7, 65e7 };
stock_t pop_15_to_44_6 = { 70e7, 70e7};
stock_t pop_45_to_64_10 = { 19e7, 19e7};
stock_t pop_65_plus_14 = { 6e7, 6e7};

stock_t industrial_capital_52 = { 2.1e11, 2.1e11 };
stock_t service_capital_67 = { 1.44e11, 1.44e11 };

stock_t nr_resources_129 = { 1e12, 1e12 };

stock_t pers_pollution_142 = { 2.5e7, 2.5e7 };

stock_t agr_inp_99 = { 5e9, 5e9 };
stock_t arable_land_85 = { 0.9e9, 0.9e9 };
stock_t yield_tech_LYTD = { 1, 1 };
stock_t labor_util_fr_del_82 = { 1, 1 };
stock_t land_fertility_121 = { 600, 600 };
stock_t perc_food_ratio_128 = { 1, 1 };
stock_t pot_arable_land_86 = { 2.3e9, 2.3e9 };
stock_t res_tech_NRTD = { 1, 1 };
stock_t ppoll_tech_PTD = { 1, 1 };
stock_t urban_ind_land_120 = { 8.2e6, 8.2e6 };

// Math functions

typedef struct {
        double val;
} smooth_t;

double smth1(double target, double timecnst)
{
        
        return 0;
}

double smth3(double target, double timecnst)
{
        return 0;
}

double min(double x, double y) 
{
        return (x < y)? x : y;
}

//

void update(double time, double dt)
{
        //
        double population_1 = pop_0_to_14_2.val + pop_15_to_44_6.val + pop_45_to_64_10.val + pop_65_plus_14.val; 

        //
        double ppoll_index_143 = pers_pollution_142.val / ppoll_in_1970_143;
        double land_fert_degr_rt_122 = graph_value_at(&land_fert_degr_rt_122_graph, ppoll_index_143); 
        double land_fert_degr_123 = land_fertility_121.val * land_fert_degr_rt_122;

        //
        double p_land_yield_fact_2_104 = smth3(yield_tech_LYTD.val, tech_dev_del_TDD);
        double s_land_yield_fact_104 = (time > t_policy_year_150)? p_land_yield_fact_2_104 : p_land_yield_fact_1_104;

        //
        double nr_res_fr_remain_133 = nr_resources_129.val / nr_resources_129.init;
        double p_fr_cap_al_obt_res_2_136 = graph_value_at(&p_fr_cap_al_obt_res_2_136_graph, nr_res_fr_remain_133);
        double p_fr_cap_al_obt_res_1_135 = graph_value_at(&p_fr_cap_al_obt_res_1_135_graph, nr_res_fr_remain_133);
        double s_fr_cap_al_obt_res_134 = (time > t_fcaor_time)? p_fr_cap_al_obt_res_2_136 : p_fr_cap_al_obt_res_1_135;
        double capacity_util_fr_83 = graph_value_at(&capacity_util_fr_83_graph, labor_util_fr_del_82.val);
        double p_nr_res_use_fact_2_131 = smth3(res_tech_NRTD.val, tech_dev_del_TDD);
        double s_nr_res_use_fact_131 = (time > t_policy_year_150)? p_nr_res_use_fact_2_131 : p_nr_res_use_fact_1_131;
        double ind_cap_out_ratio_2_ICOR2T = graph_value_at(&ind_cap_out_ratio_2_ICOR2T_graph, s_nr_res_use_fact_131);
        double yield_tech_mult_icor_COYM = graph_value_at(&yield_tech_mult_icor_COYM_graph, s_land_yield_fact_104);
        double p_ppoll_gen_fact_2_138 = smth3(ppoll_tech_PTD.val, tech_dev_del_TDD);
        double s_ppoll_gen_fact_138 = (time > t_policy_year_150)? p_ppoll_gen_fact_2_138 : p_ppoll_gen_fact_1_138;
        double ppoll_tech_mult_icor_COPM = graph_value_at(&ppoll_tech_mult_icor_COPM_graph, s_ppoll_gen_fact_138);
        double p_ind_cap_out_ratio_2_51 = ind_cap_out_ratio_2_ICOR2T * yield_tech_mult_icor_COYM * ppoll_tech_mult_icor_COPM;
        double s_ind_cap_out_ratio_51 = (time > t_policy_year_150)? p_ind_cap_out_ratio_2_51 : p_ind_cap_out_ratio_1_51;
        double industrial_output_50 = industrial_capital_52.val * (1 - s_fr_cap_al_obt_res_134) * capacity_util_fr_83 / s_ind_cap_out_ratio_51;
        double ind_out_pc_49 = industrial_output_50 / population_1;

        //
        double p_fr_inp_for_land_maint_126 = graph_value_at(&p_fr_inp_for_land_maint_126_graph, perc_food_ratio_128.val);
        double agr_inp_per_hect_101 = agr_inp_99.val * (1 - p_fr_inp_for_land_maint_126) / arable_land_85.val;
        double land_yield_mlt_cap_102 = graph_value_at(&land_yield_mlt_cap_102_graph, agr_inp_per_hect_101);
        double p_yield_mlt_air_poll_2_107 = graph_value_at(&p_yield_mlt_air_poll_2_107_graph, industrial_output_50/ind_out_in_1970_107);
        double p_yield_mlt_air_poll_1_106 = graph_value_at(&p_yield_mlt_air_poll_1_106_graph, industrial_output_50/ind_out_in_1970_107);
        double s_yield_mlt_air_poll_105 = (time > t_air_poll_time)? p_yield_mlt_air_poll_2_107 : p_yield_mlt_air_poll_1_106;
        double land_yield_103 = s_land_yield_fact_104 * land_fertility_121.val * land_yield_mlt_cap_102 * s_yield_mlt_air_poll_105;
        double food_87 = land_yield_103 * arable_land_85.val * land_fr_harvested_87 * (1 - processing_loss_87);
        double food_pc__88 = food_87 / population_1;
        double lifet_mlt_food_20 = graph_value_at(&lifet_mlt_food_20_graph, food_pc__88 / subsist_food_pc_127);
        double food_ratio_127 = food_pc__88 / subsist_food_pc_127;

        //
        double s_serv_cap_out_ratio_72 = (time > t_policy_year_150)? p_serv_cap_out_ratio_2_72 : p_serv_cap_out_ratio_1_72;
        double service_output_70 = (service_capital_67.val * capacity_util_fr_83) / s_serv_cap_out_ratio_72;
        double serv_out_pc_71 = service_output_70 / population_1;

        //
        double jobs_per_ind_cap_unit_75 = graph_value_at(&jobs_per_ind_cap_unit_75_graph, ind_out_pc_49); 
        double pot_jobs_ind_sector_74 = industrial_capital_52.val * jobs_per_ind_cap_unit_75;
        double jobs_per_hect_79 = graph_value_at(&jobs_per_hect_79_graph, agr_inp_per_hect_101);
        double pot_jobs_agr_sector_78 = jobs_per_hect_79 * arable_land_85.val;
        double jobs_per_serv_cap_unit_77 = graph_value_at(&jobs_per_serv_cap_unit_77_graph, serv_out_pc_71);
        double pot_jobs_in_serv_sector_76 = service_capital_67.val * jobs_per_serv_cap_unit_77;
        double jobs_73 = pot_jobs_ind_sector_74 + pot_jobs_agr_sector_78 + pot_jobs_in_serv_sector_76;

        //
        double hlth_serv_al_pc_21 = graph_value_at(&hlth_serv_al_pc_21_graph, serv_out_pc_71);
        double eff_hlth_serv_pc_22 = smth1(hlth_serv_al_pc_21, hlth_serv_impact_del_22);
        double lifet_mlt_hlth_serv_2_25 = graph_value_at(&lifet_mlt_hlth_serv_2_25_graph, eff_hlth_serv_pc_22);
        double lifet_mlt_hlth_serv_1_24 = graph_value_at(&lifet_mlt_hlth_serv_1_24_graph, eff_hlth_serv_pc_22);
        double lifet_mult_hlth_serv_23 = (time > 1940)? lifet_mlt_hlth_serv_2_25 : lifet_mlt_hlth_serv_1_24;
        double lifet_mlt_ppoll_29 = graph_value_at(&lifet_mlt_ppoll_29_graph, ppoll_index_143);
        double crowd_mult_ind_27 = graph_value_at(&crowd_mult_ind_27_graph, ind_out_pc_49);
        double fr_pop_urban_26 = graph_value_at(&fr_pop_urban_26_graph, population_1);
        double lifet_mlt_crowd_28 = 1 - (crowd_mult_ind_27 * fr_pop_urban_26);
        double life_expectancy_19 = life_expect_norm_19 * lifet_mlt_food_20 * lifet_mult_hlth_serv_23 * lifet_mlt_ppoll_29 * lifet_mlt_crowd_28;

        // 
        double mortal_0_to_14_4 = graph_value_at(&mortal_0_to_14_4_graph, life_expectancy_19);
        double deaths_0_to_14_3 = pop_0_to_14_2.val * mortal_0_to_14_4;
        double mortal_15_to_44_8 = graph_value_at(&mortal_15_to_44_8_graph, life_expectancy_19);
        double deaths_15_to_44_7 = pop_15_to_44_6.val * mortal_15_to_44_8;
        double mortal_45_to_64_12 = graph_value_at(&mortal_45_to_64_12_graph, life_expectancy_19);
        double deaths_45_to_64_11 = pop_45_to_64_10.val * mortal_45_to_64_12;
        double mortal_65_plus_16 = graph_value_at(&mortal_65_plus_16_graph, life_expectancy_19);
        double deaths_65_plus_15 = pop_65_plus_14.val * mortal_65_plus_16;
        double deaths_17 = deaths_0_to_14_3 + deaths_15_to_44_7 + deaths_45_to_64_11 + deaths_65_plus_15;

        //
        double labor_force_80 = (pop_15_to_44_6.val + pop_45_to_64_10.val) * labor_force_partic_80;
        double labor_util_fr_81 = jobs_73 / labor_force_80;
        double chg_lab_util_fr_del_82 = (labor_util_fr_81 - labor_util_fr_del_82.val) / labor_util_fr_del_time_82;

        // 
        double p_yield_tech_chg_mlt_LYCM = graph_value_at(&p_yield_tech_chg_mlt_LYCM_graph, des_food_ratio_DFR - food_ratio_127);
        double yield_tech_chg_rt_LYTDR = (time > t_policy_year_150)? p_yield_tech_chg_mlt_LYCM * yield_tech_LYTD.val : 0;

        //
        double p_indic_food_pc_1_90 = graph_value_at(&p_indic_food_pc_1_90_graph, ind_out_pc_49);
        double p_indic_food_pc_2_91 = graph_value_at(&p_indic_food_pc_2_91_graph, ind_out_pc_49);
        double s_indic_food_pc_89 = (time > t_policy_year_150)? p_indic_food_pc_2_91 : p_indic_food_pc_1_90;
        double p_fr_io_al_agr_2_95 = graph_value_at(&p_fr_io_al_agr_2_95_graph, food_pc__88 / s_indic_food_pc_89);
        double p_fr_io_al_agr_1_94 = graph_value_at(&p_fr_io_al_agr_1_94_graph, food_pc__88 / s_indic_food_pc_89);
        double s_fioa_agr_93 = (time > t_policy_year_150)? p_fr_io_al_agr_2_95 : p_fr_io_al_agr_1_94;

        //
        double p_indic_serv_pc_2_62 = graph_value_at(&p_indic_serv_pc_2_62_graph, ind_out_pc_49);
        double p_indic_serv_pc_1_61 = graph_value_at(&p_indic_serv_pc_1_61_graph, ind_out_pc_49);
        double s_indic_serv_pc_60 = (time > t_policy_year_150)? p_indic_serv_pc_2_62 : p_indic_serv_pc_1_61;
        double p_fr_io_al_serv_1_64 = graph_value_at(&p_fr_io_al_serv_1_64_graph, serv_out_pc_71 / s_indic_serv_pc_60);
        double p_fr_io_al_serv_2_65 = graph_value_at(&p_fr_io_al_serv_2_65_graph, serv_out_pc_71 / s_indic_serv_pc_60);
        double s_fioa_serv_63 = (time > t_policy_year_150)? p_fr_io_al_serv_2_65 : p_fr_io_al_serv_1_64;
        double p_fioa_cons_var_59 = graph_value_at(&p_fioa_cons_var_59_graph, ind_out_pc_49/ind_out_pc_des_59);
        double s_fioa_cons_const_58 = (time > t_policy_year_150)? p_fioa_cons_const_2_58 : p_fioa_cons_const_1_58;
        double s_fioa_cons_57 = (time > t_ind_equil_time_57)? p_fioa_cons_var_59 : s_fioa_cons_const_58;
        double fioa_ind_56 = (1 - s_fioa_agr_93 - s_fioa_serv_63 - s_fioa_cons_57);
        double s_avg_life_ind_cap_54 = (time > t_policy_year_150)? p_avg_life_ind_cap_2_54 : p_avg_life_ind_cap_1_54;
        double ind_cap_invest_55 = fioa_ind_56 * industrial_output_50;
        double ind_cap_deprec_53 = industrial_capital_52.val / s_avg_life_ind_cap_54;

        //
        double s_avg_life_agr_inp_100 = (time > t_policy_year_150)? p_avg_life_agr_inp_2_100 : p_avg_life_agr_inp_1_100;
        double tot_agric_invest_92 = industrial_output_50 * s_fioa_agr_93;
        double dev_cost_per_hect_97 = graph_value_at(&dev_cost_per_hect_97_graph, pot_arable_land_86.val / pot_arable_land_tot_84);
        double marg_prod_land_dev_109 = land_yield_103 / (dev_cost_per_hect_97 * social_discount_109);
        double marg_land_yield_mlt_cap_111 = graph_value_at(&marg_land_yield_mlt_cap_111_graph, agr_inp_per_hect_101);
        double marg_prod_agr_inp_110 = s_avg_life_agr_inp_100 * land_yield_103 * marg_land_yield_mlt_cap_111 / land_yield_mlt_cap_102;
        double fr_inp_al_land_dev_108 = graph_value_at(&fr_inp_al_land_dev_108_graph, marg_prod_land_dev_109 / marg_prod_agr_inp_110);
        double current_agr_inp_98 = tot_agric_invest_92 * (1 - fr_inp_al_land_dev_108);
        double chg_agr_inp_99 = (current_agr_inp_98 - agr_inp_99.val) / s_avg_life_agr_inp_100;

        // 
        double avg_ind_out_pc_43 = smth1(ind_out_pc_49, income_expect_avg_time_43);
        double fam_income_expect_42 = (ind_out_pc_49 - avg_ind_out_pc_43) / avg_ind_out_pc_43;
        double fam_resp_to_soc_norm_41 = graph_value_at(&fam_resp_to_soc_norm_41_graph, fam_income_expect_42);
        double del_ind_out_pc_40 = smth3(ind_out_pc_49, social_adj_del_40);
        double soc_fam_size_norm_39 = graph_value_at(&soc_fam_size_norm_39_graph, del_ind_out_pc_40);
        double des_compl_fam_size_38 = (time > t_zero_pop_grow_time_38)? 2.0 : (des_compl_fam_size_norm_38* fam_resp_to_soc_norm_41 * soc_fam_size_norm_39);
        double perc_life_expectancy_37 = smth3(life_expectancy_19, lifet_perc_del_37);
        double compl_mlt_perc_lifet_36 = graph_value_at(&compl_mlt_perc_lifet_36_graph, perc_life_expectancy_37);
        double des_tot_fert_35 = des_compl_fam_size_38 * compl_mlt_perc_lifet_36;
        double fecundity_mult_34 = graph_value_at(&fecundity_mult_34_graph, life_expectancy_19);
        double max_tot_fert_33 = max_tot_fert_norm_33 * fecundity_mult_34;
        double need_for_fert_cont_44 = (max_tot_fert_33 / des_tot_fert_35) - 1;
        double fr_serv_al_fert_cont_48 = graph_value_at(&fr_serv_al_fert_cont_48_graph, need_for_fert_cont_44);
        double fert_cont_al_pc_47 = fr_serv_al_fert_cont_48 * serv_out_pc_71;
        double fert_cont_facil_pc_46 = smth3(fert_cont_al_pc_47, hlth_serv_impact_del_22);
        double fert_cont_eff_table_45 = graph_value_at(&fert_cont_eff_table_45_graph, fert_cont_facil_pc_46);
        double fert_cont_eff_45 = (time > t_fert_cont_eff_time_45)? 1 : fert_cont_eff_table_45;
        double total_fertility_32 = min(max_tot_fert_33, (max_tot_fert_33 * (1 - fert_cont_eff_45) + des_tot_fert_35 * fert_cont_eff_45));
        double births_30 = (time > t_pop_equil_time_30)? deaths_17 : (total_fertility_32 * pop_15_to_44_6.val * 0.5 / reproductive_lifetime_30);
        double matur_14_to_15_5 = pop_0_to_14_2.val * (1 - mortal_0_to_14_4) / 15;
        double matur_44_to_45_9 = pop_15_to_44_6.val * (1 - mortal_15_to_44_8) / 30;
        double matur_64_to_65_13 = pop_45_to_64_10.val * (1 - mortal_45_to_64_12) / 20;

        double land_devel_rt_96 = tot_agric_invest_92 * fr_inp_al_land_dev_108 / dev_cost_per_hect_97;

        double urb_ind_land_pc_117 = graph_value_at(&urb_ind_land_pc_117_graph, ind_out_pc_49);
        double urb_ind_land_req_118 = urb_ind_land_pc_117 * population_1;
        double land_rem_urb_ind_use_119 = (urb_ind_land_req_118 - urban_ind_land_120.val) / urb_ind_land_dev_time_119;

        double p_land_life_mlt_yield_1_114 = graph_value_at(&p_land_life_mlt_yield_1_114_graph, land_yield_103 / inherent_land_fert_124);
        double p_land_life_mlt_yield_2_115 = graph_value_at(&p_land_life_mlt_yield_2_115_graph, land_yield_103 / inherent_land_fert_124);
        double s_land_life_mlt_yield_113 = (time > t_land_life_time)? 
                pow(0.95, time - t_land_life_time) * p_land_life_mlt_yield_1_114 + (1 - pow(0.95, time - t_land_life_time)) * p_land_life_mlt_yield_2_115 
                : p_land_life_mlt_yield_1_114;

        double avg_life_land_112 = avg_life_land_norm_112 * s_land_life_mlt_yield_113;
        double land_erosion_rt_116 = arable_land_85.val / avg_life_land_112;

        double pc_res_use_mlt_132 = graph_value_at(&pc_res_use_mlt_132_graph, ind_out_pc_49);
        double ppoll_gen_agr_140 = agr_inp_per_hect_101 * arable_land_85.val * fr_agr_inp_pers_mtl_140 * agr_mtl_toxic_index_140;
        double ppoll_gen_ind_139 = pc_res_use_mlt_132 * population_1 * frac_res_pers_mtl_139 * ind_mtl_emiss_fact_139 * ind_mtl_toxic_index_139;
        double ppoll_gen_rt_137 = (ppoll_gen_ind_139 + ppoll_gen_agr_140) * s_ppoll_gen_fact_138;
        double ppoll_appear_rt_141 = smth3(ppoll_gen_rt_137, ppoll_trans_del_141);
        double assim_half_life_mlt_145 = graph_value_at(&assim_half_life_mlt_145_graph, ppoll_index_143);

        double assim_half_life_146 = assim_half_life_1970_146 * assim_half_life_mlt_145;

        double ppoll_assim_rt_144 = pers_pollution_142.val / (assim_half_life_146 * 1.4);

        double land_fert_regen_time_125 = graph_value_at(&land_fert_regen_time_125_graph, p_fr_inp_for_land_maint_126);
        double land_fert_regen_124 = (inherent_land_fert_124 - land_fertility_121.val) / land_fert_regen_time_125;

        double chg_perc_food_ratio = (food_ratio_127 - perc_food_ratio_128.val) / food_short_perc_del_128;

        double serv_cap_invest_66 = industrial_output_50 * s_fioa_serv_63;
        double s_avg_life_serv_cap_69 = (time > t_policy_year_150)? p_avg_life_serv_cap_2_69 : p_avg_life_serv_cap_1_69;
        double serv_cap_deprec_68 = service_capital_67.val / s_avg_life_serv_cap_69;

        double nr_res_use_rate_130 = population_1 * pc_res_use_mlt_132 * s_nr_res_use_fact_131;

        double p_res_tech_chg_mlt_NRCM = graph_value_at(&p_res_tech_chg_mlt_NRCM_graph, 1 - nr_res_use_rate_130 / des_res_use_rt_DNRUR);
        double res_tech_chg_rt_NRATE = (time > t_policy_year_150)? p_res_tech_chg_mlt_NRCM * res_tech_NRTD.val : 0;

        double p_ppoll_tech_chg_mlt_POLGFM = graph_value_at(&p_ppoll_tech_chg_mlt_POLGFM_graph, 1 - ppoll_index_143 / des_ppoll_index_DPOLX);
        double ppoll_tech_chg_rt_PTDR = (time > t_policy_year_150)? p_ppoll_tech_chg_mlt_POLGFM * ppoll_tech_PTD.val : 0;

        // new state
        agr_inp_99.val = agr_inp_99.val + (chg_agr_inp_99) * dt;
        industrial_capital_52.val = industrial_capital_52.val + (ind_cap_invest_55 - ind_cap_deprec_53) * dt;
        arable_land_85.val = arable_land_85.val + (land_devel_rt_96 - land_rem_urb_ind_use_119 - land_erosion_rt_116) * dt;
        pop_0_to_14_2.val = pop_0_to_14_2.val + (births_30 - matur_14_to_15_5 - deaths_0_to_14_3) * dt;
        pop_15_to_44_6.val = pop_15_to_44_6.val + (matur_14_to_15_5 - matur_44_to_45_9 - deaths_15_to_44_7) * dt;
        pop_45_to_64_10.val = pop_45_to_64_10.val + (matur_44_to_45_9 - matur_64_to_65_13 - deaths_45_to_64_11) * dt;
        pop_65_plus_14.val = pop_65_plus_14.val + (matur_64_to_65_13 - deaths_65_plus_15) * dt;
        yield_tech_LYTD.val = yield_tech_LYTD.val + yield_tech_chg_rt_LYTDR * dt;
        labor_util_fr_del_82.val = labor_util_fr_del_82.val + (chg_lab_util_fr_del_82) * dt;
        land_fertility_121.val = land_fertility_121.val + (land_fert_regen_124 - land_fert_degr_123) * dt;
        pers_pollution_142.val = pers_pollution_142.val + (ppoll_appear_rt_141 - ppoll_assim_rt_144) * dt;
        perc_food_ratio_128.val = perc_food_ratio_128.val + (chg_perc_food_ratio) * dt;
        service_capital_67.val = service_capital_67.val + (serv_cap_invest_66 - serv_cap_deprec_68) * dt;
        nr_resources_129.val = nr_resources_129.val + (- nr_res_use_rate_130) * dt;
        pot_arable_land_86.val = pot_arable_land_86.val + (- land_devel_rt_96) * dt;
        res_tech_NRTD.val = res_tech_NRTD.val + (res_tech_chg_rt_NRATE) * dt;
        ppoll_tech_PTD.val = ppoll_tech_PTD.val + (ppoll_tech_chg_rt_PTDR) * dt;
        urban_ind_land_120.val = urban_ind_land_120.val + (land_rem_urb_ind_use_119) * dt;
} 

int main()
{
        double x = -0.5;
        
        for (int i = 0; i < 35; i++) {
                double value = graph_value_at(&p_fr_io_al_agr_2_95_graph, x);
                printf("%g %g\n", x, value);
                x += 0.1;
        }
        return 0;
}
