/**
 *
 * Installs and configures the XDEBUG extension for PHP5
 */
class phpfpm::extensions::xdebug (
  $remote_enable      = "On",
  $remote_host        = "host.kala",
  $remote_port        = 9000,
  $remote_handler     = "dbgp",
  $remote_auto        = "On",
  $remote_cb          = 1,
  $profiler_enable    = 1,
  $profile_output_dir = "/tmp/xprofile",
  $collect_params     = "On",
  $show_local_vars    = "On",) {
  phpfpm::extension { "php5-xdebug": version => present, }

  exec { "appendxdebug":
    path    => "/bin:/usr/bin",
    unless  => "grep ${remote_host} /etc/php5/conf.d/xdebug.ini",
    command => "sed -i '\$a xdebug.remote_enable=${remote_enable}' /etc/php5/conf.d/xdebug.ini && sed -i '\$a xdebug.remote_host=${remote_host}' /etc/php5/conf.d/xdebug.ini && sed -i '\$a xdebug.remote_port=${remote_port}' /etc/php5/conf.d/xdebug.ini && sed -i '\$a xdebug.remote_handler=${remote_handler}' /etc/php5/conf.d/xdebug.ini && sed -i '\$a xdebug.remote_connect_back=${remote_cb}' /etc/php5/conf.d/xdebug.ini && sed -i '\$a xdebug.remote_autostart=${remote_auto}' /etc/php5/conf.d/xdebug.ini",
    require => Package["php5-xdebug"],
    notify  => [Class["phpfpm::service"], Class["nginx::service"]],
  }

  exec { "/usr/bin/perl -p0i -e 's/^/$::kalahost host.kala\n/;' '/etc/hosts'":
    unless      => "/bin/grep -Fxqe '$::kalahost host.kala' '/etc/hosts'",
    path        => "/bin",
    refreshonly => $refreshonly,
    require => Package["php5-xdebug"],
    notify  => [Class["phpfpm::service"], Class["nginx::service"]],
  }
}
