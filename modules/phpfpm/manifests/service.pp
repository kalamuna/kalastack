
class phpfpm::service {

	service { "php5-fpm":
		ensure 	=> running,
		require => Class["phpfpm::install"],
	}
	
}