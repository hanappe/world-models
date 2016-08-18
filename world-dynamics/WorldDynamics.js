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

function WorldDynamicsGraph(values)
{
        this.valueAt = function(x) 
        {
                var pi = values[0];
                var xi = pi[0];
                var yi = pi[1];
                if (x < xi) {
                        return yi;
                }
                var pj, xj, yj;
                for (var i = 1; i < values.length; i++) {       
                        pj = values[i];
                        xj = pj[0];
                        yj = pj[1];
                        if ((xi <= x) && (x < xj)) {
                                return yi + (yj - yi) * (x - xi) / (xj - xi);
                        }
                        xi = xj;
                        yi = yj;
                }
                return yj;
        }
}


function WorldDynamics(args)
{
        // Constants

        this.birthRateNormal = 0.04; 
        this.birthRateNormal1 = 0.04; 
        this.deathRateNormal = 0.028; 
        this.deathRateNormal1 = 0.028; 
        this.effectiveCapitalInvestmentRatioNormal = 1.0;
        this.naturalResourcesInitial = (3.6e9 * 250.0 * 1.0);
        this.naturalResourceUsageNormal = 1.0;
        this.naturalResourceUsageNormal1 = 1.0;
        this.landArea = 135e6;
        this.populationDensityNormal = 26.5;
        this.foodCoefficient = 1.0;
        this.foodCoefficient1 = 1.0;
        this.foodNormal = 1.0;
        this.capitalInvestmentInAgricultureFractionNormal = 0.3;
        this.capitalInvestmentGenerationNormal = 0.05;
        this.capitalInvestmentGenerationNormal1 = 0.05;
        this.capitalInvestmentDiscardNormal = 0.025;
        this.capitalInvestmentDiscardNormal1 = 0.025;
        this.pollutionStandard = 3.6e9;
        this.pollutionNormal = 1.0;
        this.pollutionNormal1 = 1.0;
        this.switchTime6 = 1970;
        this.capitalInvestmentInAgricultureFractionAdjTime = 15.0;
        this.qualityOfLifeStandard = 1.0;

        // State variables

        this.population = 1.65e9;
        this.naturalResources = this.naturalResourcesInitial; 
        this.capitalInvestment = 0.4e9;
        this.pollution = 0.2e9; 
        this.capitalInvestmentInAgricultureFraction = 0.2;
        this.qualityOfLife = 0;
        
        // Tables

        this.birthRateFromMaterialMultiplierTable = new WorldDynamicsGraph([[0.0, 1.2],  
                                                                            [1.0, 1.0],  
                                                                            [2.0, 0.85], 
                                                                            [3.0, 0.75],  
                                                                            [4.0, 0.7],  
                                                                            [5.0, 0.7]]);

        this.naturalResourceExtractionMultiplierTable = new WorldDynamicsGraph([[0.0,  0.0],
                                                                                [0.25, 0.15],
                                                                                [0.5,  0.5],
                                                                                [0.75, 0.85],
                                                                                [1.0,  1.0]]);

        this.deathRateFromMaterialMultiplierTable = new WorldDynamicsGraph([[0.0, 3.0],
                                                                            [0.5, 1.8],
                                                                            [1.0, 1.0],
                                                                            [1.5, 0.8],
                                                                            [2.0, 0.7],
                                                                            [2.5, 0.6],
                                                                            [3.0, 0.53],
                                                                            [3.5, 0.5],
                                                                            [4.0, 0.5],
                                                                            [4.5, 0.5],
                                                                            [5.0, 0.5]]);

        this.deathRateFromPollutionMultiplierTable = new WorldDynamicsGraph([[0.0,  0.92],
                                                                             [10.0, 1.3],
                                                                             [20.0, 2.0],
                                                                             [30.0, 3.2],
                                                                             [40.0, 4.8],
                                                                             [50.0, 6.8],
                                                                             [60.0, 9.2]]);

        this.deathRateFromFoodMultiplierTable = new WorldDynamicsGraph([[0.0,  30.0],
                                                                        [0.25,  3.0],
                                                                        [0.5,  2.0],
                                                                        [0.75, 1.4],
                                                                        [1.0,  1.0],
                                                                        [1.25, 0.7],
                                                                        [1.5,  0.6],
                                                                        [1.75, 0.5],
                                                                        [2.0,  0.5]]);

        this.deathRateFromCrowdingMultiplierTable = new WorldDynamicsGraph([[0.0, 0.9],
                                                                            [1.0, 1.0],
                                                                            [2.0, 1.2],
                                                                            [3.0, 1.5],
                                                                            [4.0, 1.9],
                                                                            [5.0, 3.0]]);
                
        this.birthRateFromCrowdingMultiplierTable = new WorldDynamicsGraph([[0.0, 1.05],
                                                                            [1.0, 1.0],
                                                                            [2.0, 0.9],
                                                                            [3.0, 0.7],
                                                                            [4.0, 0.6],
                                                                            [5.0, 0.55]]);

        this.birthRateFromFoodMultiplierTable = new WorldDynamicsGraph([[0.0, 0.0],
                                                                        [1.0, 1.0],
                                                                        [2.0, 1.6],
                                                                        [3.0, 1.9],
                                                                        [4.0, 2.0]]);

        this.birthRateFromPollutionMultiplierTable = new WorldDynamicsGraph([[0.0,  1.02],
                                                                             [10.0, 0.9],
                                                                             [20.0, 0.7],
                                                                             [30.0, 0.4],
                                                                             [40.0, 0.25],
                                                                             [50.0, 0.15],
                                                                             [60.0, 0.1]]);

        this.foodFromCrowdingMultiplierTable = new WorldDynamicsGraph([[0.0, 2.4],
                                                                       [1.0, 1.0],
                                                                       [2.0, 0.6],
                                                                       [3.0, 0.4],
                                                                       [4.0, 0.3],
                                                                       [5.0, 0.2]]);

        this.foodPotentialFromCapitalInvestmentTable = new WorldDynamicsGraph([[0.0, 0.5],
                                                                               [1.0, 1.0],
                                                                               [2.0, 1.4],
                                                                               [3.0, 1.7],
                                                                               [4.0, 1.9],
                                                                               [5.0, 2.05],
                                                                               [6.0, 2.2]]);

        this.capitalInvestmentMultiplierTable = new WorldDynamicsGraph([[0.0, 0.1],
                                                                        [1.0, 1.0],
                                                                        [2.0, 1.8],
                                                                        [3.0, 2.4],
                                                                        [4.0, 2.8],
                                                                        [5.0, 3.0]]);

        this.foodFromPollutionMultiplierTable = new WorldDynamicsGraph([[0.0,  1.02],
                                                                        [10.0, 0.9],
                                                                        [20.0, 0.65],
                                                                        [30.0, 0.35],
                                                                        [40.0, 0.2],
                                                                        [50.0, 0.1],
                                                                        [60.0, 0.05]]);

        this.pollutionFromCapitalMultiplierTable = new WorldDynamicsGraph([[0.0, 0.05],
                                                                           [1.0, 1.0],
                                                                           [2.0, 3.5],
                                                                           [3.0, 5.4],
                                                                           [4.0, 7.4],
                                                                           [5.0, 8.0]]);

        this.pollutionAbsorptionTimeTable = new WorldDynamicsGraph([[0.0,   0.6],
                                                                    [10.0,  2.5],
                                                                    [20.0,  5.0],
                                                                    [30.0,  8.0],
                                                                    [40.0, 11.5],
                                                                    [50.0, 15.5],
                                                                    [60.0, 20.0]]);

        this.capitalFractionIndicatedByFoodRatioTable = new WorldDynamicsGraph([[0.0, 1.0],
                                                                                [0.5, 0.6],
                                                                                [1.0, 0.3],
                                                                                [1.5, 0.15],
                                                                                [2.0, 0.1]]);

        this.qualityOfLifeFromMaterialTable = new WorldDynamicsGraph([[0.0, 0.2],
                                                                      [1.0, 1.0],
                                                                      [2.0, 1.7],
                                                                      [3.0, 2.3],
                                                                      [4.0, 2.7],
                                                                      [5.0, 2.9]]);

        this.qualityOfLifeFromCrowdingTable = new WorldDynamicsGraph([[0.0, 2.0],
                                                                      [0.5, 1.3],
                                                                      [1.0, 1.0],
                                                                      [1.5, 0.75],
                                                                      [2.0, 0.55],
                                                                      [2.5, 0.45],
                                                                      [3.0, 0.38],
                                                                      [3.5, 0.3],
                                                                      [4.0, 0.25],
                                                                      [4.5, 0.22],
                                                                      [5.0, 0.2]]);

        this.qualityOfLifeFromFoodTable = new WorldDynamicsGraph([[0.0, 0.0],
                                                                  [1.0, 1.0],
                                                                  [2.0, 1.8],
                                                                  [3.0, 2.4],
                                                                  [4.0, 2.7]]);

        this.qualityOfLifeFromPollutionTable = new WorldDynamicsGraph([[0.0, 1.04],
                                                                       [10.0, 0.85],
                                                                       [20.0, 0.6],
                                                                       [30.0, 0.3],
                                                                       [40.0, 0.15],
                                                                       [50.0, 0.05],
                                                                       [60.0, 0.02]]);

        this.naturalResourceFromMaterialMultiplierTable = new WorldDynamicsGraph([[0.0, 0.0],
                                                                                  [1.0, 1.0],
                                                                                  [2.0, 1.8],
                                                                                  [3.0, 2.4],
                                                                                  [4.0, 2.9],
                                                                                  [5.0, 3.3],
                                                                                  [6.0, 3.6],
                                                                                  [7.0, 3.8],
                                                                                  [8.0, 3.9],
                                                                                  [9.0, 3.95],
                                                                                  [10.0, 4.0]]);

        this.capitalInvestmentFromQualityRatioTable = new WorldDynamicsGraph([[0.0, 0.7],
                                                                              [0.5, 0.8],
                                                                              [1.0, 1.0],
                                                                              [1.5, 1.5],
                                                                              [2.0, 2.0]]);

        this.clip = function(value1, value2, switchTime, t) 
        {
                return (t <= switchTime)? value1 : value2;
        }

        this.update = function(t, dt) 
        {
                this.capitalInvestmentRatio = this.capitalInvestment / this.population;
                
                this.naturalResourceFractionRemaining = this.naturalResources / this.naturalResourcesInitial;
                this.naturalResourceExtractionMultiplier 
                = this.naturalResourceExtractionMultiplierTable.valueAt(this.naturalResourceFractionRemaining);

                this.capitalInvestmentRatioInAgriculture = (this.capitalInvestmentRatio 
                                                            * this.capitalInvestmentInAgricultureFraction
                                                            / this.capitalInvestmentInAgricultureFractionNormal);

                // p.37: the effective capital investment ratio has
                // been defined so that the "normal" value in 1970
                // should be 1.
                this.effectiveCapitalInvestmentRatio = (this.capitalInvestmentRatio
                                                        * this.naturalResourceExtractionMultiplier
                                                        * (1.0 - this.capitalInvestmentInAgricultureFraction)
                                                        / (1.0 - this.capitalInvestmentInAgricultureFractionNormal));
                
                this.materialStandardOfLiving = this.effectiveCapitalInvestmentRatio / this.effectiveCapitalInvestmentRatioNormal;


                this.crowdingRatio = this.population / (this.landArea * this.populationDensityNormal);

                this.pollutionRatio = this.pollution / this.pollutionStandard; 

                this.foodFromPollutionMultiplier = this.foodFromPollutionMultiplierTable.valueAt(this.pollutionRatio);

                this.foodFromCrowdingMultiplier = this.foodFromCrowdingMultiplierTable.valueAt(this.crowdingRatio);
                this.foodPotentialFromCapitalInvestment 
                        = this.foodPotentialFromCapitalInvestmentTable.valueAt(this.capitalInvestmentRatioInAgriculture);

                this.foodRatio = (this.foodPotentialFromCapitalInvestment
                                  * this.foodFromCrowdingMultiplier
                                  * this.foodFromPollutionMultiplier
                                  * this.clip(this.foodCoefficient, this.foodCoefficient1, 1970, t) 
                                  / this.foodNormal);


                this.deathRateFromMaterialMultiplier = this.deathRateFromMaterialMultiplierTable.valueAt(this.materialStandardOfLiving);
                this.deathRateFromPollutionMultiplier = this.deathRateFromPollutionMultiplierTable.valueAt(this.pollutionRatio);
                this.deathRateFromFoodMultiplier = this.deathRateFromFoodMultiplierTable.valueAt(this.foodRatio);
                this.deathRateFromCrowdingMultiplier = this.deathRateFromCrowdingMultiplierTable.valueAt(this.crowdingRatio);

                this.deathRatePerYear = (this.clip(this.deathRateNormal, this.deathRateNormal, 1970, t)
                                         * this.deathRateFromMaterialMultiplier
                                         * this.deathRateFromPollutionMultiplier
                                         * this.deathRateFromFoodMultiplier
                                         * this.deathRateFromCrowdingMultiplier);

                this.deathsPerYear = this.deathRatePerYear * this.population;
                this.deaths = this.deathsPerYear * dt;
                
                this.birthRateFromFoodMultiplier = this.birthRateFromFoodMultiplierTable.valueAt(this.foodRatio); 
                this.birthRateFromPollutionMultiplier = this.birthRateFromPollutionMultiplierTable.valueAt(this.pollutionRatio);
                this.birthRateFromMaterialMultiplier = this.birthRateFromMaterialMultiplierTable.valueAt(this.materialStandardOfLiving);
                this.birthRateFromCrowdingMultiplier = this.birthRateFromCrowdingMultiplierTable.valueAt(this.crowdingRatio);
                
                this.birthRatePerYear = (this.clip(this.birthRateNormal, this.birthRateNormal1, 1970, t)
                                         * this.birthRateFromFoodMultiplier 
                                         * this.birthRateFromMaterialMultiplier
                                         * this.birthRateFromCrowdingMultiplier
                                         * this.birthRateFromPollutionMultiplier);
                this.birthsPerYear = this.birthRatePerYear * this.population;
                this.births = this.birthsPerYear * dt;

                this.naturalResourceFromMaterialMultiplier 
                        = this.naturalResourceFromMaterialMultiplierTable.valueAt(this.materialStandardOfLiving);

                this.naturalResourcesUsageRate = (this.population 
                                                  * this.clip(this.naturalResourceUsageNormal, 
                                                              this.naturalResourceUsageNormal1,
                                                              1970, t)
                                                  * this.naturalResourceFromMaterialMultiplier);
                
                this.capitalInvestmentMultiplier = this.capitalInvestmentMultiplierTable.valueAt(this.materialStandardOfLiving);
                
                this.capitalInvestmentGeneration = (this.population 
                                                    * this.capitalInvestmentMultiplier
                                                    * this.clip(this.capitalInvestmentGenerationNormal,
                                                                this.capitalInvestmentGenerationNormal1,
                                                                1970, t));
                this.capitalInvestmentDiscard = (this.capitalInvestment 
                                                 * this.clip(this.capitalInvestmentDiscardNormal, 
                                                             this.capitalInvestmentDiscardNormal1,
                                                             1970, t));

                this.pollutionFromCapitalMultiplier = this.pollutionFromCapitalMultiplierTable.valueAt(this.capitalInvestmentRatio);

                this.pollutionGeneration = (this.population 
                                            * this.pollutionFromCapitalMultiplier
                                            * this.clip(this.pollutionNormal, 
                                                        this.pollutionNormal1,
                                                        this.switchTime6,
                                                        t));

                this.pollutionAbsorptionTime = this.pollutionAbsorptionTimeTable.valueAt(this.pollutionRatio);
                this.pollutionAbsorption = this.pollution / this.pollutionAbsorptionTime;

                this.capitalFractionIndicatedByFoodRatio = this.capitalFractionIndicatedByFoodRatioTable.valueAt(this.foodRatio);

                this.qualityOfLifeFromMaterial = this.qualityOfLifeFromMaterialTable.valueAt(this.materialStandardOfLiving);
                this.qualityOfLifeFromCrowding = this.qualityOfLifeFromCrowdingTable.valueAt(this.crowdingRatio);
                this.qualityOfLifeFromFood = this.qualityOfLifeFromFoodTable.valueAt(this.foodRatio);
                this.qualityOfLifeFromPollution = this.qualityOfLifeFromPollutionTable.valueAt(this.pollutionRatio);

                this.capitalInvestmentFromQualityRatio 
                        = this.capitalInvestmentFromQualityRatioTable.valueAt(this.qualityOfLifeFromMaterial 
                                                                              / this.qualityOfLifeFromFood);

                this.qualityOfLife = (this.qualityOfLifeStandard 
                                      * this.qualityOfLifeFromMaterial
                                      * this.qualityOfLifeFromCrowding
                                      * this.qualityOfLifeFromFood
                                      * this.qualityOfLifeFromPollution);
                
                // Update the state variables
                this.population = this.population + this.births - this.deaths;
                this.naturalResources = this.naturalResources - this.naturalResourcesUsageRate * dt;
                this.capitalInvestment = (this.capitalInvestment 
                                          + (this.capitalInvestmentGeneration - this.capitalInvestmentDiscard) * dt);
                this.pollution = this.pollution + (this.pollutionGeneration - this.pollutionAbsorption) * dt;

                this.capitalInvestmentInAgricultureFraction = (this.capitalInvestmentInAgricultureFraction 
                                                               + ((dt / this.capitalInvestmentInAgricultureFractionAdjTime)
                                                                  * (this.capitalFractionIndicatedByFoodRatio
                                                                     * this.capitalInvestmentFromQualityRatio
                                                                     - this.capitalInvestmentInAgricultureFraction)));
        } 
}
