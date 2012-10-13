/**
 * 
 * Installs and configures PHP5-FPM so that php5 works on nginx
 * 
 */
class phpfpm {
	
	include phpfpm::install, phpfpm::config, phpfpm::service
	
}