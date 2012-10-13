/**
 * 
 * This is a basic definition for creating a drupal based nginx vhost file
 * 
 */

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

    # Enable the site if enabled = true
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
    
    # Only make the site available
    else {
        file { "/etc/nginx/sites-available/${vhost}":
            ensure  => file,
            content => template("drupal/nginx/vhost.conf.erb"),
            notify  => Class["nginx::service"],
            require => Class["nginx::install"],
        }
    }
    
}
