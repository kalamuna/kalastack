/**
 * 
 * Installst the nginx package
 * 
 */
class nginx::install {
    
	package { "nginx":
		ensure => "present",
	}
	
}
