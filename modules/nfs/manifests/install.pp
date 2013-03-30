/**
 * 
 * Makes sure nfs is installed
 * 
 */
class nfs::install {

  package { "nfs-common":
    ensure => present,
  }

}