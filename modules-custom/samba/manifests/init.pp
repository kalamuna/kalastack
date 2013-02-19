/**
 * 
 * Installs and configures samba
 * 
 */
class samba {
    
	include samba::install, samba::config, samba::service
	
}