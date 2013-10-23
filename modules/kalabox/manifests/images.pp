/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
class kalabox::images {
    # Makes a nginx vhost for phpmyadmin
  phpfpm::nginx::vhost { "images":
    vhost       => "images",
    root        => "/etc/kalastack/images",
    server_name => "images.kala",
    index       => "index.html",
    upstream    => "unix:/tmp/php-fpm.sock",
    custom      => "",
    require     => Class["nginx"],
    options     => {},
  }

}
