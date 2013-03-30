/**
 * 
 * Makes sure nfs is running
 * 
 */
class nfs::service {

  service { "nfs-common":
    ensure    => running,
    require   => Class["nfs::install"],
  }

}