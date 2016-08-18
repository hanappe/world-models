set terminal postscript color

#set out "Population.ps"
#plot "WorldDynamics.dat" using 1:2 with lines title "Population"

#set out "NaturalResources.ps"
#plot "WorldDynamics.dat" using 1:3 with lines title "Natural Resources"

#set out "CapitalInvestment.ps"
#plot "WorldDynamics.dat" using 1:4 with lines title "Capital Investment"

#set out "PollutionRatio.ps"
#plot "WorldDynamics.dat" using 1:5 with lines title "Pollution Ratio"

#set out "QualityOfLife.ps"
#plot "WorldDynamics.dat" using 1:6 with lines title "Quality of Life"

#set out "CapitalInvestmentRatios.ps"
#plot "WorldDynamics.dat" using 1:7 with lines title "Capital investment ratio", \
#     "WorldDynamics.dat" using 1:8 with lines title "Effective capital investment ratio", \
#     "WorldDynamics.dat" using 1:10 with lines title "Capital investment ratio in agriculture", \
#     "WorldDynamics.dat" using 1:11 with lines title "Capital investment ratio (effective + agriculture)"


set out "WorldDynamics.ps"
#set multiplot
set multiplot layout 3,2 columnsfirst
#set size 1,1
#set origin 0,0
plot "WorldDynamics.dat" using 1:2 with lines title "Population"
plot "WorldDynamics.dat" using 1:3 with lines title "Natural Resources"
plot "WorldDynamics.dat" using 1:4 with lines title "Capital Investment"
plot "WorldDynamics.dat" using 1:5 with lines title "Pollution Ratio"
plot "WorldDynamics.dat" using 1:6 with lines title "Quality of Life"
unset multiplot
