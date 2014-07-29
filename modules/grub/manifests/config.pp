/**
 * Provides some custom grub config
 */
class grub::config {

  exec { "notimeout":
    path    => "/bin:/usr/bin",
    unless  => "grep timeout=3 /etc/grub.d/00_header",
    command => "sed -i -e \"s/set timeout=-1/set timeout=3/g\" /etc/grub.d/00_header",
  }

  exec { "rebuildgrub":
    path        => "/bin:/usr/bin:/usr/sbin",
    subscribe  => Exec['notimeout'],
    command => "sudo update-grub",
  }
  
}