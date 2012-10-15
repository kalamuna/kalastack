/**
 * 
 * Provides a basic hosts file
 * 
 */
class network::config {
    
	file { "/etc/hosts" :
		ensure => present,
	}
	
	prepend_if_no_such_line { "kala":
	   file => "/etc/hosts",
	   line => "127.0.0.1  kala",
	   require => File["/etc/hosts"]
	}
	
	prepend_if_no_such_line { "php.kala":
       file => "/etc/hosts",
       line => "127.0.0.1  php.kala",
       require => File["/etc/hosts"]
    }
	
}