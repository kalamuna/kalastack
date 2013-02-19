/**
 * 
 * Installs PHP5 for CLI
 * 
 */
class php5::install {
	
	package { "php5-cli":
		ensure => "5.3.10-1ubuntu3.4",
	}
	
}
