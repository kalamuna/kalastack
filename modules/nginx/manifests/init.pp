/**
 * 
 * Installs and configures nginx
 * 
 */
class nginx {
    
	include nginx::install, nginx::service
	
}