
class phpfpm::install {
	
	include php5
	
	package { "php5-fpm":
		ensure => installed,
	}
}