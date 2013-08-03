/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
class kalabox::start {
    # Makes a nginx vhost for phpmyadmin
  phpfpm::nginx::vhost { "start":
    vhost       => "start",
    root        => "/usr/share/kalabox",
    server_name => "start.kala",
    index       => "index.php",
    upstream    => "unix:/tmp/php-fpm.sock",
    custom      => "",
    require     => Class["nginx"],
    options     => {},
  }

  file { "/usr/share/kalabox/index.php":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/kalabox/index.php",
  }

  file { "/usr/share/kalabox/kalaboxv2.png":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/kalabox/kalaboxv2.png",
  }

  file { "/usr/share/kalabox/kalaboxv2.ico":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/kalabox/kalaboxv2.ico",
  }

}
