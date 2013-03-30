/**
 *
 * Configures nfs
 */
class nfs::config {

  exec { "nfsconfig":
    path    => "/bin:/usr/bin",
    unless  => "cat /etc/fstab | grep \"nfs-server:/   /mnt   nfs    auto  0  0\"",
    command => "sudo sed -i '$ a\nfs-server:/   /mnt   nfs    auto  0  0' /etc/fstap",
    require => Class["nfs::install"],
    notify => Class["nfs::service"],
  }

}