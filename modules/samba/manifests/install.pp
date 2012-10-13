/**
 * 
 * Installs samba
 * 
 */
class samba::install {
    
	package { "samba" : 
		ensure => "2:3.6.3-2ubuntu2.3",
	}
	
}