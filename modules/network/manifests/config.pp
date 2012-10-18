/**
 * 
 * Provides a basic hosts file
 * 
 */
class network::config {
    
	file { "/etc/hosts" :
		ensure => present,
	}
	
  file { "/etc/network/interfaces" :
    ensure => present,
    content => template("network/interfaces.erb"),
    owner => "root",
    group => "root",
  }
  
  exec { "vboxnetup":
    path => "/bin:/usr/bin",
    command => "ifconfig eth1 192.168.56.101 netmask 255.255.255.0 up",
    subscribe   => File["/etc/network/interfaces"],
    refreshonly => true
  }
	
	network::prepend { "kala":
	  file => "/etc/hosts",
	  line => "127.0.0.1  kala",
	  require => File["/etc/hosts"],
	}
	
	network::prepend { "host.kala":
    file => "/etc/hosts",
    line => "192.168.56.1  host.kala",
    require => File["/etc/hosts"],
  }
	
	network::prepend  { "php.kala":
    file => "/etc/hosts",
    line => "127.0.0.1  php.kala",
    require => File["/etc/hosts"],
  }
  
  
	
}