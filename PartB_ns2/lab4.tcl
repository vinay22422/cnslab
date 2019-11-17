set ns [new Simulator]
set nf [open lab.tr w]
set tf [open lab.nam w]
$ns trace-all $nf
$ns namtrace-all $tf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$ns make-lan "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n4 $n5 $n6" 10Mb 10ms LL Queue/DropTail Mac/802_3
$ns duplex-link $n3 $n6 100Mb 10ms DropTail

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

set null5 [new Agent/Null]
$ns attach-agent $n5 $null5

$ns connect $udp1 $null5

$cbr1 set packetSize_ 500Mb
$cbr1 set interval_ 0.005

set err [new ErrorModel]
$ns lossmodel $err $n3 $n6
$err set rate_ 0.2

proc finish { } {
global ns nf tf
$ns flush-trace
exec nam lab.nam &
close $tf
close $nf
set ctr0 0
set thr0 0
set fid [open lab.tr r]
while {[gets $fid line] != -1} {
	if { [string match "*r*" $line] } {
		set fields [regexp -all -inline {\S+} $line]
		set c2 [lindex $fields 2]
		set c3 [lindex $fields 3]
		if { [expr $c2==8] && [expr $c3==5] } {
			set ctr0 [expr $ctr0 + 1]
		}
	}
}
set thr0 [expr $ctr0/5]
puts "No of packets: $ctr0"
puts "Throughput: $thr0"
exit 0
}
$ns at 0.01 "$cbr1 start"
$ns at 5.0 "finish"
$ns run
