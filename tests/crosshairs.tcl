source base.tcl

set w .line
set graph [bltLineGraph $w]

$graph crosshairs configure -hide no
$graph crosshairs configure -x 200 -y 200

echo "Testing Crosshairs..."
$graph crosshairs configure

bltTest2 $graph crosshairs -color green
bltTest2 $graph crosshairs -dashes "8 3"
bltTest2 $graph crosshairs -hide yes
bltTest2 $graph crosshairs -linewidth 3
bltTest2 $graph crosshairs -x 100
bltTest2 $graph crosshairs -y 100

bltCmd $graph crosshairs cget -color
bltCmd $graph crosshairs configure
bltCmd $graph crosshairs configure -color
bltCmd $graph crosshairs on
bltCmd $graph crosshairs off
bltCmd $graph crosshairs toggle

echo "done"
bltPlotDestroy $w

