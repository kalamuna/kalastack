define network::interface (
	$style, 
	$ip = $::ipaddress, 
	$gateway = $::netmask) {
		
    file { "/etc/network/interfaces":
        owner => root,
        group => root,
        mode => 644,
        content => template("network/${style}")
    }
}
