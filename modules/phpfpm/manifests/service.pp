/**
 * 
 * Makes sure PHP5-FPM is running
 * 
 */
class phpfpm::service {

	service { "php5-fpm":
		ensure 	=> running,
		require => Class["phpfpm::install"],
	}
	
}