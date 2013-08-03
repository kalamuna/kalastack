/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
class kalabox::aliases {
    # Makes a nginx vhost for phpmyadmin
  phpfpm::nginx::vhost { "aliases":
    vhost       => "aliases",
    root        => "/usr/share/kalaaliases",
    server_name => "aliases.kala",
    index       => "index.php",
    upstream    => "unix:/tmp/php-fpm.sock",
    custom      => "",
    require     => Class["nginx"],
    options     => {},
  }

  file { "/usr/share/kalaaliases/index.php":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/kalabox/aliases.php",
  }
}
