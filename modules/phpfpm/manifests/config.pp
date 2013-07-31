/**
 *
 * Configures PHP5-FPM
 * Creates a basic pool
 * Loads all PHP extensions
 *
 */
class phpfpm::config {

	# Dynamically set php memory limit, but don't exceed 1G
	$php_mem_limit = $::kalamem / 4
	if ($php_mem_limit > 1024) {
		$php_mem_limit_use = 1024
	}
	else {
		$php_mem_limit_use = $::kalamem / 4
	}

	php5::ini { "fpm":
	  path     => "/etc/php5/fpm/php.ini",
	  require  => Class["phpfpm::install"],
	  notify => Class["phpfpm::service"],
	  max_execution_time => 900,
	  memory_limit => "${php_mem_limit_use}M",
	}

	file { "/etc/php5/fpm/pool.d/www.conf":
	  ensure 	=> file,
	  content => template("phpfpm/www.conf.erb"),
	  require  => Class["phpfpm::install"],
	  notify => Class["phpfpm::service"],
	}

	include phpfpm::extensions::apc
	include phpfpm::extensions::xdebug
	include phpfpm::extensions::curl
	include phpfpm::extensions::imap
	include phpfpm::extensions::pear
	include phpfpm::extensions::gd
	include phpfpm::extensions::mcrypt

}
