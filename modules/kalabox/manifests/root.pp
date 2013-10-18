/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
class kalabox::root {
    # Makes a nginx vhost for phpmyadmin
  phpfpm::nginx::vhost { "root":
    vhost       => "root",
    root        => "/var/www",
    server_name => "root.kala",
    index       => "index.html",
    upstream    => "unix:/tmp/php-fpm.sock",
    custom      => "",
    require     => Class["nginx"],
    options     => {},
  }

}
