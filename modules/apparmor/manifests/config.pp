/**
 *
 * Class that governs the creation of the mysql-server configuration
 *
 */
class apparmor::config {

  file { "/etc/apparmor.d/usr.sbin.mysqld":
    ensure => present,
    source => "puppet:///modules/apparmor/usr.sbin.mysqld",
    notify => Class["apparmor::service"],
    subscribe => Exec["movedata"],
  }

}
