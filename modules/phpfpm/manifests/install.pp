
class phpfpm::install {
	
	include php5
	
	package { "php5-fpm":
		ensure => "5.3.10-1ubuntu3.4",
	}
}