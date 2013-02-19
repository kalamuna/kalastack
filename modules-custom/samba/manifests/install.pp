/**
 * 
 * Installs samba
 * 
 */
class samba::install {
    
	package { "samba" : 
		ensure => "present",
	}
	
}
