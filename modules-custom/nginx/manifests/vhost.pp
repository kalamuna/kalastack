/**
 * 
 * Basic definition for a barebones nginx vhost
 * 
 */
define nginx::vhost (
    
	$vhost = $title,
	$root = "/var/www", 
	$server_name = "_",
	
) {
	
	file { "/etc/nginx/sites-available/${vhost}":
		ensure 	=> file,
		content => template("nginx/vhost.conf.erb"),
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
	
}