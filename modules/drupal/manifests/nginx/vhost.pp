
define drupal::nginx::vhost (
    $vhost = $title,
    $root = "/var/www/drupal",
    $server_name = "_",
    $index = "index.php",
    $upstream = "unix:/tmp/php-fpm.sock",
    $custom = "",
    $options = {},
    $enabled = TRUE,
) {
    
    include nginx

    if ($enabled == TRUE) {
        file { "/etc/nginx/sites-enabled/${vhost}":
            ensure  => link,
            target  => "/etc/nginx/sites-available/${vhost}",
            require => Class["nginx::install"],
        }  
        
        file { "/etc/nginx/sites-available/${vhost}":
            ensure  => file,
            content => template("drupal/nginx/vhost.conf.erb"),
            require => [
                File["/etc/nginx/sites-enabled/${vhost}"],
            ],
            notify  => Class["nginx::service"],
        }
    }
    else {
        file { "/etc/nginx/sites-available/${vhost}":
            ensure  => file,
            content => template("drupal/nginx/vhost.conf.erb"),
            notify  => Class["nginx::service"],
        }
    }
    
    file { $root:
        ensure => "directory",
        owner  => "www-data",
        group  => "www-data",
        mode   => 755,
    }
}
