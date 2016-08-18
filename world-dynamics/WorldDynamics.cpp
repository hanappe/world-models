//
// World Dynamics, based on Jay Wright Forrester's book.
//
// Copyright (c) 2009, Sony Computer Science Laboratory Paris
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Sony Computer Science Laboratory Paris nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY Sony Computer Science Laboratory Paris ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Peter Hanappe
//

#include <stdio.h>
#include <stdarg.h>

class WorldDynamicsGraph
{
public:
        int n;
        double* values;

        WorldDynamicsGraph() {
                n = 0;
                values = 0;
        }

        ~WorldDynamicsGraph() {
                if (values) delete[] values;
        }

        void init(int num, ...) {
                n = num;
                values = new double[2*n];

                va_list ap;
                va_start(ap, num);
                for (int i = 0; i < 2 * n; i++) {
                        double v = va_arg(ap, double);
                        values[i] = v;
                }
                va_end(ap);
        }

        double valueAt(double x) {
                double xi = values[0];
                double yi = values[1];
                if (x < xi) {
                        return yi;
                }
                double xj, yj;
                for (int i = 1; i < n; i++) {       
                        xj = values[2 * i];
                        yj = values[2 * i + 1];
                        if ((xi <= x) && (x < xj)) {
                                double y = yi + (yj - yi) * (x - xi) / (xj - xi);
                                return y;
                        }
                        xi = xj;
                        yi = yj;
                }
                return yj;
        }
};


class WorldDynamics
{
public:

        // Constants
        static const double birthRateNormal = 0.04; 
        static const double birthRateNormal1 = 0.04; 
        static const double deathRateNormal = 0.028; 
        static const double deathRateNormal1 = 0.028; 
        static const double effectiveCapitalInvestmentRatioNormal = 1.0;
        static const double naturalResourcesInitial = (3.6e9 * 250.0 * 1.0);
        static const double naturalResourceUsageNormal = 1.0;
        static const double naturalResourceUsageNormal1 = 1.0;
        //static const double naturalResourceUsageNormal1 = 0.25;
        static const double landArea = 135e6;
        static const double populationDensityNormal = 26.5;
        static const double foodCoefficient = 1.0;
        static const double foodCoefficient1 = 1.0;
        static const double foodNormal = 1.0;
        static const double capitalInvestmentInAgricultureFractionNormal = 0.3;
        static const double capitalInvestmentGenerationNormal = 0.05;
        static const double capitalInvestmentGenerationNormal1 = 0.05;
        static const double capitalInvestmentDiscardNormal = 0.025;
        static const double capitalInvestmentDiscardNormal1 = 0.025;
        static const double pollutionStandard = 3.6e9;
        static const double pollutionNormal = 1.0;
        static const double pollutionNormal1 = 1.0;
        static const double switchTime6 = 1970;
        static const double capitalInvestmentInAgricultureFractionAdjTime = 15.0;
        static const double qualityOfLifeStandard = 1.0;
        
        // Tables
        WorldDynamicsGraph birthRateFromMaterialMultiplierTable;
        WorldDynamicsGraph naturalResourceExtractionMultiplierTable;
        WorldDynamicsGraph deathRateFromMaterialMultiplierTable;
        WorldDynamicsGraph deathRateFromPollutionMultiplierTable;
        WorldDynamicsGraph deathRateFromFoodMultiplierTable;
        WorldDynamicsGraph deathRateFromCrowdingMultiplierTable;
        WorldDynamicsGraph birthRateFromCrowdingMultiplierTable;
        WorldDynamicsGraph birthRateFromFoodMultiplierTable;
        WorldDynamicsGraph birthRateFromPollutionMultiplierTable;
        WorldDynamicsGraph foodFromCrowdingMultiplierTable;
        WorldDynamicsGraph foodPotentialFromCapitalInvestmentTable;
        WorldDynamicsGraph capitalInvestmentMultiplierTable;
        WorldDynamicsGraph foodFromPollutionMultiplierTable;
        WorldDynamicsGraph pollutionFromCapitalMultiplierTable;
        WorldDynamicsGraph pollutionAbsorptionTimeTable;
        WorldDynamicsGraph capitalFractionIndicatedByFoodRatioTable;
        WorldDynamicsGraph qualityOfLifeFromMaterialTable;
        WorldDynamicsGraph qualityOfLifeFromCrowdingTable;
        WorldDynamicsGraph qualityOfLifeFromFoodTable;
        WorldDynamicsGraph qualityOfLifeFromPollutionTable;
        WorldDynamicsGraph naturalResourceFromMaterialMultiplierTable;
        WorldDynamicsGraph capitalInvestmentFromQualityRatioTable;

        // State variables
        double population;
        double naturalResources;
        double capitalInvestment;
        double pollution;
        double capitalInvestmentInAgricultureFraction;

        // Calculated variables
        double qualityOfLife;
        double capitalInvestmentRatio;
        double effectiveCapitalInvestmentRatio;
        double capitalInvestmentRatioInAgriculture;
        double effectiveCapitalInvestmentRatioNominal;
        double naturalResourceFractionRemaining;
        double naturalResourceExtractionMultiplier; 
        double materialStandardOfLiving;
        double crowdingRatio;
        double pollutionRatio;
        double foodFromPollutionMultiplier;
        double foodFromCrowdingMultiplier;
        double foodPotentialFromCapitalInvestment;        
        double foodRatio;
        double deathRateFromMaterialMultiplier;
        double deathRateFromPollutionMultiplier;
        double deathRateFromFoodMultiplier;
        double deathRateFromCrowdingMultiplier;
        double deathRatePerYear;
        double deathsPerYear;
        double deaths;
        double birthRateFromFoodMultiplier;
        double birthRateFromPollutionMultiplier;
        double birthRateFromMaterialMultiplier;
        double birthRateFromCrowdingMultiplier;
        double birthRatePerYear;
        double birthsPerYear;
        double births;
        double naturalResourceFromMaterialMultiplier;                
        double naturalResourcesUsageRate;
        double capitalInvestmentMultiplier;
        double capitalInvestmentGeneration;
        double capitalInvestmentDiscard;
        double pollutionFromCapitalMultiplier;
        double pollutionGeneration;
        double pollutionAbsorptionTime;
        double pollutionAbsorption;
        double capitalFractionIndicatedByFoodRatio;
        double qualityOfLifeFromMaterial;
        double qualityOfLifeFromCrowding;
        double qualityOfLifeFromFood;
        double qualityOfLifeFromPollution;
        double capitalInvestmentFromQualityRatio;

        WorldDynamics() 
        {
                // State variables
                population = 1.65e9;
                naturalResources = naturalResourcesInitial; 
                capitalInvestment = 0.4e9;
                pollution = 0.2e9; 
                capitalInvestmentInAgricultureFraction = 0.2;

                // Tables

                birthRateFromMaterialMultiplierTable.init(6,
                                                          0.0, 1.2,  
                                                          1.0, 1.0,  
                                                          2.0, 0.85, 
                                                          3.0, 0.75,  
                                                          4.0, 0.7,  
                                                          5.0, 0.7);

                naturalResourceExtractionMultiplierTable.init(5,
                                                              0.0,  0.0,
                                                              0.25, 0.15,
                                                              0.5,  0.5,
                                                              0.75, 0.85,
                                                              1.0,  1.0);

                deathRateFromMaterialMultiplierTable.init(11,
                                                          0.0, 3.0,
                                                          0.5, 1.8,
                                                          1.0, 1.0,
                                                          1.5, 0.8,
                                                          2.0, 0.7,
                                                          2.5, 0.6,
                                                          3.0, 0.53,
                                                          3.5, 0.5,
                                                          4.0, 0.5,
                                                          4.5, 0.5,
                                                          5.0, 0.5);

                deathRateFromPollutionMultiplierTable.init(7,
                                                           0.0,  0.92,
                                                           10.0, 1.3,
                                                           20.0, 2.0,
                                                           30.0, 3.2,
                                                           40.0, 4.8,
                                                           50.0, 6.8,
                                                           60.0, 9.2);

                deathRateFromFoodMultiplierTable.init(9,
                                                      0.0,  30.0,
                                                      0.25,  3.0,
                                                      0.5,  2.0,
                                                      0.75, 1.4,
                                                      1.0,  1.0,
                                                      1.25, 0.7,
                                                      1.5,  0.6,
                                                      1.75, 0.5,
                                                      2.0,  0.5);

                deathRateFromCrowdingMultiplierTable.init(6,
                                                          0.0, 0.9,
                                                          1.0, 1.0,
                                                          2.0, 1.2,
                                                          3.0, 1.5,
                                                          4.0, 1.9,
                                                          5.0, 3.0);
                
                birthRateFromCrowdingMultiplierTable.init(6,
                                                          0.0, 1.05,
                                                          1.0, 1.0,
                                                          2.0, 0.9,
                                                          3.0, 0.7,
                                                          4.0, 0.6,
                                                          5.0, 0.55);

                birthRateFromFoodMultiplierTable.init(5,
                                                      0.0, 0.0,
                                                      1.0, 1.0,
                                                      2.0, 1.6,
                                                      3.0, 1.9,
                                                      4.0, 2.0);

                birthRateFromPollutionMultiplierTable.init(7,
                                                           0.0,  1.02,
                                                           10.0, 0.9,
                                                           20.0, 0.7,
                                                           30.0, 0.4,
                                                           40.0, 0.25,
                                                           50.0, 0.15,
                                                           60.0, 0.1);

                foodFromCrowdingMultiplierTable.init(6,
                                                     0.0, 2.4,
                                                     1.0, 1.0,
                                                     2.0, 0.6,
                                                     3.0, 0.4,
                                                     4.0, 0.3,
                                                     5.0, 0.2);

                foodPotentialFromCapitalInvestmentTable.init(7,
                                                             0.0, 0.5,
                                                             1.0, 1.0,
                                                             2.0, 1.4,
                                                             3.0, 1.7,
                                                             4.0, 1.9,
                                                             5.0, 2.05,
                                                             6.0, 2.2);

                capitalInvestmentMultiplierTable.init(6,
                                                      0.0, 0.1,
                                                      1.0, 1.0,
                                                      2.0, 1.8,
                                                      3.0, 2.4,
                                                      4.0, 2.8,
                                                      5.0, 3.0);

                foodFromPollutionMultiplierTable.init(7,
                                                      0.0,  1.02,
                                                      10.0, 0.9,
                                                      20.0, 0.65,
                                                      30.0, 0.35,
                                                      40.0, 0.2,
                                                      50.0, 0.1,
                                                      60.0, 0.05);

                pollutionFromCapitalMultiplierTable.init(6,
                                                         0.0, 0.05,
                                                         1.0, 1.0,
                                                         2.0, 3.5,
                                                         3.0, 5.4,
                                                         4.0, 7.4,
                                                         5.0, 8.0);

                pollutionAbsorptionTimeTable.init(7,
                                                  0.0,   0.6,
                                                  10.0,  2.5,
                                                  20.0,  5.0,
                                                  30.0,  8.0,
                                                  40.0, 11.5,
                                                  50.0, 15.5,
                                                  60.0, 20.0);

                capitalFractionIndicatedByFoodRatioTable.init(5,
                                                              0.0, 1.0,
                                                              0.5, 0.6,
                                                              1.0, 0.3,
                                                              1.5, 0.15,
                                                              2.0, 0.1);

                qualityOfLifeFromMaterialTable.init(6,
                                                    0.0, 0.2,
                                                    1.0, 1.0,
                                                    2.0, 1.7,
                                                    3.0, 2.3,
                                                    4.0, 2.7,
                                                    5.0, 2.9);

                qualityOfLifeFromCrowdingTable.init(11,
                                                    0.0, 2.0,
                                                    0.5, 1.3,
                                                    1.0, 1.0,
                                                    1.5, 0.75,
                                                    2.0, 0.55,
                                                    2.5, 0.45,
                                                    3.0, 0.38,
                                                    3.5, 0.3,
                                                    4.0, 0.25,
                                                    4.5, 0.22,
                                                    5.0, 0.2);

                qualityOfLifeFromFoodTable.init(5,
                                                0.0, 0.0,
                                                1.0, 1.0,
                                                2.0, 1.8,
                                                3.0, 2.4,
                                                4.0, 2.7);

                qualityOfLifeFromPollutionTable.init(7,
                                                     0.0, 1.04,
                                                     10.0, 0.85,
                                                     20.0, 0.6,
                                                     30.0, 0.3,
                                                     40.0, 0.15,
                                                     50.0, 0.05,
                                                     60.0, 0.02);

                naturalResourceFromMaterialMultiplierTable.init(11,
                                                                0.0, 0.0,
                                                                1.0, 1.0,
                                                                2.0, 1.8,
                                                                3.0, 2.4,
                                                                4.0, 2.9,
                                                                5.0, 3.3,
                                                                6.0, 3.6,
                                                                7.0, 3.8,
                                                                8.0, 3.9,
                                                                9.0, 3.95,
                                                                10.0, 4.0);

                capitalInvestmentFromQualityRatioTable.init(5,
                                                            0.0, 0.7,
                                                            0.5, 0.8,
                                                            1.0, 1.0,
                                                            1.5, 1.5,
                                                            2.0, 2.0);
        }

        double clip(double value1, double value2, double switchTime, double t) 
        {
                return (t <= switchTime)? value1 : value2;
        }

        void update(double t, double dt) 
        {
                capitalInvestmentRatio = capitalInvestment / population;
                
                naturalResourceFractionRemaining = naturalResources / naturalResourcesInitial;
                naturalResourceExtractionMultiplier 
                        = naturalResourceExtractionMultiplierTable.valueAt(naturalResourceFractionRemaining);

                capitalInvestmentRatioInAgriculture = (capitalInvestmentRatio 
                                                       * capitalInvestmentInAgricultureFraction
                                                       / capitalInvestmentInAgricultureFractionNormal);

                // debug
                effectiveCapitalInvestmentRatioNominal = (capitalInvestmentRatio
                                                          * (1.0 - capitalInvestmentInAgricultureFraction));

                // p.37: the effective capital investment ratio has
                // been defined so that the "normal" value in 1970
                // should be 1.
                effectiveCapitalInvestmentRatio = (capitalInvestmentRatio
                                                   * naturalResourceExtractionMultiplier
                                                   * (1.0 - capitalInvestmentInAgricultureFraction)
                                                   / (1.0 - capitalInvestmentInAgricultureFractionNormal));
                                                          
                materialStandardOfLiving = effectiveCapitalInvestmentRatio / effectiveCapitalInvestmentRatioNormal;


                crowdingRatio = population / (landArea * populationDensityNormal);

                pollutionRatio = pollution / pollutionStandard; 

                foodFromPollutionMultiplier = foodFromPollutionMultiplierTable.valueAt(pollutionRatio);

                foodFromCrowdingMultiplier = foodFromCrowdingMultiplierTable.valueAt(crowdingRatio);
                foodPotentialFromCapitalInvestment 
                        = foodPotentialFromCapitalInvestmentTable.valueAt(capitalInvestmentRatioInAgriculture);

                foodRatio = (foodPotentialFromCapitalInvestment
                                    * foodFromCrowdingMultiplier
                                    * foodFromPollutionMultiplier
                                    * clip(foodCoefficient, foodCoefficient1, 1970, t) 
                                    / foodNormal);


                deathRateFromMaterialMultiplier = deathRateFromMaterialMultiplierTable.valueAt(materialStandardOfLiving);
                deathRateFromPollutionMultiplier = deathRateFromPollutionMultiplierTable.valueAt(pollutionRatio);
                deathRateFromFoodMultiplier = deathRateFromFoodMultiplierTable.valueAt(foodRatio);
                deathRateFromCrowdingMultiplier = deathRateFromCrowdingMultiplierTable.valueAt(crowdingRatio);

                deathRatePerYear = (clip(deathRateNormal, deathRateNormal, 1970, t)
                                           * deathRateFromMaterialMultiplier
                                           * deathRateFromPollutionMultiplier
                                           * deathRateFromFoodMultiplier
                                           * deathRateFromCrowdingMultiplier);

                deathsPerYear = deathRatePerYear * population;
                deaths = deathsPerYear * dt;

                
                birthRateFromFoodMultiplier = birthRateFromFoodMultiplierTable.valueAt(foodRatio); 
                birthRateFromPollutionMultiplier = birthRateFromPollutionMultiplierTable.valueAt(pollutionRatio);
                birthRateFromMaterialMultiplier = birthRateFromMaterialMultiplierTable.valueAt(materialStandardOfLiving);
                birthRateFromCrowdingMultiplier = birthRateFromCrowdingMultiplierTable.valueAt(crowdingRatio);
                
                birthRatePerYear = (clip(birthRateNormal, birthRateNormal1, 1970, t)
                                           * birthRateFromFoodMultiplier 
                                           * birthRateFromMaterialMultiplier
                                           * birthRateFromCrowdingMultiplier
                                           * birthRateFromPollutionMultiplier);
                birthsPerYear = birthRatePerYear * population;
                births = birthsPerYear * dt;

                naturalResourceFromMaterialMultiplier 
                        = naturalResourceFromMaterialMultiplierTable.valueAt(materialStandardOfLiving);

                naturalResourcesUsageRate = (population 
                                                    * clip(naturalResourceUsageNormal, 
                                                           naturalResourceUsageNormal1,
                                                           1970, t)
                                                    * naturalResourceFromMaterialMultiplier);
                
                capitalInvestmentMultiplier = capitalInvestmentMultiplierTable.valueAt(materialStandardOfLiving);

                capitalInvestmentGeneration = (population 
                                                      * capitalInvestmentMultiplier
                                                      * clip(capitalInvestmentGenerationNormal,
                                                             capitalInvestmentGenerationNormal1,
                                                             1970, t));
                capitalInvestmentDiscard = (capitalInvestment 
                                                   * clip(capitalInvestmentDiscardNormal, 
                                                          capitalInvestmentDiscardNormal1,
                                                          1970, t));

                pollutionFromCapitalMultiplier = pollutionFromCapitalMultiplierTable.valueAt(capitalInvestmentRatio);

                pollutionGeneration = (population 
                                              * pollutionFromCapitalMultiplier
                                              * clip(pollutionNormal, 
                                                     pollutionNormal1,
                                                     switchTime6,
                                                     t));

                pollutionAbsorptionTime = pollutionAbsorptionTimeTable.valueAt(pollutionRatio);
                pollutionAbsorption = pollution / pollutionAbsorptionTime;

                capitalFractionIndicatedByFoodRatio = capitalFractionIndicatedByFoodRatioTable.valueAt(foodRatio);

                qualityOfLifeFromMaterial = qualityOfLifeFromMaterialTable.valueAt(materialStandardOfLiving);
                qualityOfLifeFromCrowding = qualityOfLifeFromCrowdingTable.valueAt(crowdingRatio);
                qualityOfLifeFromFood = qualityOfLifeFromFoodTable.valueAt(foodRatio);
                qualityOfLifeFromPollution = qualityOfLifeFromPollutionTable.valueAt(pollutionRatio);

                capitalInvestmentFromQualityRatio 
                        = capitalInvestmentFromQualityRatioTable.valueAt(qualityOfLifeFromMaterial / qualityOfLifeFromFood);

                qualityOfLife = (qualityOfLifeStandard 
                                 * qualityOfLifeFromMaterial
                                 * qualityOfLifeFromCrowding
                                 * qualityOfLifeFromFood
                                 * qualityOfLifeFromPollution);

                // Update the state variables
                population = population + births - deaths;
                naturalResources = naturalResources - naturalResourcesUsageRate * dt;
                capitalInvestment = capitalInvestment + (capitalInvestmentGeneration - capitalInvestmentDiscard) * dt;
                pollution = pollution + (pollutionGeneration - pollutionAbsorption) * dt;

                capitalInvestmentInAgricultureFraction = 
                        capitalInvestmentInAgricultureFraction 
                        + ((dt / capitalInvestmentInAgricultureFractionAdjTime)
                           * (capitalFractionIndicatedByFoodRatio
                              * capitalInvestmentFromQualityRatio
                              - capitalInvestmentInAgricultureFraction));
        } 
};

int main()
{
        WorldDynamics worldDynamics;

        double time = 1900;
        double length = 2100;
        double dt = 0.2;
        
        while (time <= length) {

                worldDynamics.update(time, dt);

                printf("%g %g %g %g %g %g %g %g %g %g %g\n", 
                       time,
                       worldDynamics.population,
                       worldDynamics.naturalResources,
                       worldDynamics.capitalInvestment,
                       worldDynamics.pollutionRatio,
                       worldDynamics.qualityOfLife,
                       worldDynamics.capitalInvestmentRatio,
                       worldDynamics.effectiveCapitalInvestmentRatio,
                       worldDynamics.effectiveCapitalInvestmentRatioNominal,
                       worldDynamics.capitalInvestmentRatioInAgriculture,
                       worldDynamics.effectiveCapitalInvestmentRatio + worldDynamics.capitalInvestmentRatioInAgriculture);

                time += dt;
        }
}
