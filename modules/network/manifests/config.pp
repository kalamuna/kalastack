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
    notify => Exec["vboxnetup"],
  }
  
  exec { "vboxnetup":
    path => "/bin:/usr/bin",
    command => "ifup eth1",
    require => File["/etc/network/interfaces"],
  }
	
	network::prepend { "kala":
	  file => "/etc/hosts",
	  line => "127.0.0.1  kala",
	  require => File["/etc/hosts"],
	}
	
	network::prepend  { "php.kala":
    file => "/etc/hosts",
    line => "127.0.0.1  php.kala",
    require => File["/etc/hosts"],
  }
  
  
	
}