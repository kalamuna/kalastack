/**
 *
 * Defintion to set up a basic KALAMUNA splash screen
 * @todo derecate in favor of dashboard
 */
define phpfpm::nginx::kalabox (
  $vhost       = $title,
  $root        = "/usr/share/kalabox",
  $server_name = "_",
  $index       = "index.php",
  $upstream    = "unix:/tmp/php-fpm.sock",
  $custom      = "",
  $options     = {
  }
  ,) {
  include nginx

  file { "/etc/nginx/sites-available/${vhost}":
    ensure  => file,
    content => template("phpfpm/nginx/vhost.conf.erb"),
    require => [File["/etc/nginx/sites-enabled/${vhost}"],],
    notify  => Class["nginx::service"],
  }

  file { "/etc/nginx/sites-enabled/${vhost}":
    ensure  => link,
    target  => "/etc/nginx/sites-available/${vhost}",
    require => Class["nginx::install"],
  }

  file { $root:
    ensure => "directory",
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
  }

  file { "${root}/index.php":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/phpfpm/index.php",
  }

  file { "${root}/kalaboxv2.png":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/phpfpm/kalaboxv2.png",
  }

  file { "${root}/kalaboxv2.ico":
    ensure => present,
    owner  => $::kalauser,
    group  => $::kalauser,
    mode   => 777,
    source => "puppet:///modules/phpfpm/kalaboxv2.ico",
  }

}
