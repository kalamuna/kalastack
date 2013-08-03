/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
class kalabox::info {
    # Makes a nginx vhost for phpmyadmin
  phpfpm::nginx::vhost { "info":
    vhost       => "info",
    root        => "/usr/share/kalainfo",
    server_name => "info.kala",
    index       => "index.php",
    upstream    => "unix:/tmp/php-fpm.sock",
    custom      => "",
    require     => Class["nginx"],
    options     => {},
  }

  file { "/usr/share/kalainfo/index.php":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/kalabox/info.php",
  }
}
