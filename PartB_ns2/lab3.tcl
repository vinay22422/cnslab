set ns [new Simulator]
set nf [open lab.tr w]
$ns trace-all $nf
set tf [open lab.nam w]
$ns namtrace-all $tf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$n0 label "Source/FTP"
$n1 label "Source/TELNET"
$n3 label "Destination/FTP"
$n5 label "Destination/TELNET"

$ns duplex-link $n0 $n2 100Mb 300ms DropTail
$ns duplex-link $n1 $n2 100Mb 300ms DropTail
$ns duplex-link $n2 $n3 100Mb 300ms DropTail
$ns duplex-link $n2 $n4 100Mb 300ms DropTail
$ns duplex-link $n4 $n5 100Mb 300ms DropTail

set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set sink3 [new Agent/TCPSink]
set sink5 [new Agent/TCPSink]
set ftp0 [new Application/FTP]
set telnet1 [new Application/Telnet]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n3 $sink3
$ns attach-agent $n5 $sink5
$ftp0 attach-agent $tcp0
$telnet1 attach-agent $tcp1

$ns connect $tcp0 $sink3
$ns connect $tcp1 $sink5

$telnet1 set packetSize_ 1000Mb
$telnet1 set interval_ 0.0001

proc finish { } {
global ns nf tf
$ns flush-trace
exec nam lab.nam &
close $tf
close $nf
set ctr0 0
set ctr1 0
set thr0 0
set thr1 0
set fid [open lab.tr r]
while {[gets $fid line] != -1} {
	if {[string match "*r*" $line]} {
		set fields [regexp -all -inline {\S+} $line]
		set c2 [lindex $fields 2]
		set c3 [lindex $fields 3]
		if { [expr $c2==2] && [expr $c3==3] } {
			set ctr0 [expr $ctr0 + 1]
		}
		if { [expr $c2==4] && [expr $c3==5] } {
			set ctr1 [expr $ctr1 + 1]
		}		
	}
}
set thr0 [expr $ctr0/5]
set thr1 [expr $ctr1/5]
puts "No of packets FTP: $ctr0"
puts "Throughput FTP: $thr0"
puts "No of packets TELNET: $ctr1"
puts "Throughput TELNET: $thr1"
exit 0
}
$ns at 0.01 "$ftp0 start"
$ns at 0.01 "$telnet1 start"
$ns at 5 "finish"
$ns run
