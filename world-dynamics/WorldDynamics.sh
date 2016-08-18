#!/bin/bash

./WorldDynamics > WorldDynamics.dat

gnuplot < WorldDynamics.gnuplot

evince Population.ps NaturalResources.ps CapitalInvestment.ps PollutionRatio.ps QualityOfLife.ps &
