
define phpfpm::nginx::kalabox (
	$vhost = $title,
	$root = "/var/www",
	$server_name = "_",
	$index = "index.php",
	$upstream = "unix:/tmp/php-fpm.sock",
	$custom = "",
	$options = {}, 
){	
	
	include nginx

	file { "/etc/nginx/sites-available/${vhost}":
		ensure 	=> file,
		content => template("phpfpm/nginx/vhost.conf.erb"),
		require => [
			File["/etc/nginx/sites-enabled/${vhost}"],
		],
		notify 	=> Class["nginx::service"],
	}

	file { "/etc/nginx/sites-enabled/${vhost}":
		ensure 	=> link,
		target 	=> "/etc/nginx/sites-available/${vhost}",
		require => Class["nginx::install"],
	}
	
	file { $root:
	    ensure => "directory",
	    owner  => "www-data",
	    group  => "www-data",
	    mode   => 777,
	}
	
	file { "${root}/index.php":
	  ensure => file,
	  owner  => www-data,
	  group  => www-data,
	  mode   => 777,
	  source => "puppet:///modules/phpfpm/index.php",
	}
	
	file { "${root}/kalamuna.jpg":
	  ensure => file,
	  owner  => www-data,
	  group  => www-data,
	  mode   => 777,
	  source => "puppet:///modules/phpfpm/kalamuna.jpg",
	}
}
