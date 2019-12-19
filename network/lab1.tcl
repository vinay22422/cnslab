#initialization
set ns [new Simulator]
set nf [open lab.tr w]
$ns trace-all $nf
set tf [open lab.nam w]
$ns namtrace-all $tf


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 10Mb 300ms DropTail
$ns duplex-link $n1 $n2 10Mb 300ms DropTail
$ns duplex-link $n2 $n3 1Mb 300ms DropTail

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

$ns connect $udp0 $null0

$ns connect $udp1 $null0

$cbr1 set packetSize_ 500Mb
$cbr1 set interval_ 0.005
$cbr0 set packetSize_ 500Mb
$cbr0 set interval_ 0.005

proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf
	set ctr 0
	set fid [open lab.tr r]
	while {[gets $fid line]!=-1} {
		if {[string match "*d*" $line]} {
			set ctr [expr $ctr + 1]
		}
	}

puts "no of packets droped = $ctr"

}
$ns at 0.01 "$cbr0 start"
$ns at 0.01 "$cbr1 start"
$ns at 5.0 "finish"
$ns run



