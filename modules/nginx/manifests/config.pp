/**
 *
 * Configure nginx
 *
 */
class nginx::config {

  nginx::conf { "nginx.conf":
    path    => "/etc/nginx/nginx.conf",
    require => [Class["nginx::install"], File["/etc/kalastack/vhosts/sites-enabled"]],
    notify  => Class["nginx::service"],
  }

  file { "/etc/nginx/fastcgi_params":
    ensure => file,
    source => "puppet:///modules/nginx/fastcgi_params",
    require => Class["nginx::install"],
  }

  file { "/etc/kalastack/vhosts":
    ensure  => directory,
    mode    => 777,
    require => [Class["nginx::install"], Class["kalabox::build"]],
  }

  file { "/etc/kalastack/vhosts/sites-available":
    ensure  => directory,
    mode    => 777,
    require => File["/etc/kalastack/vhosts"],
  }

  file { "/etc/kalastack/vhosts/sites-enabled":
    ensure  => directory,
    mode    => 777,
    require => File["/etc/kalastack/vhosts"],
  }
}
