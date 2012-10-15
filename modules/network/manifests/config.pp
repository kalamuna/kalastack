/**
 * 
 * Provides a basic hosts file
 * 
 */
class network::config {
    
	file { "/etc/hosts" :
		ensure => present,
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