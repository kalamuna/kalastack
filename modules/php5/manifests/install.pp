/**
 * 
 * Installs PHP5 for CLI
 * 
 */
class php5::install {
	
	package { "php5-cli":
		ensure => present,
	}
	
}
