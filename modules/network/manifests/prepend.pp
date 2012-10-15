/**
 * 
 * Prepend a line to a file if that line doesn't already exist
 * 
 */
define network::prepend ( 
    $file, 
    $line, 
<<<<<<< HEAD
    $refreshonly = FALSE,
=======
    $refreshonly = false,
>>>>>>> ab7cab991d3b92f7fb79d4282d4f7d8ea41b04d6
) {
    
    exec { "/usr/bin/perl -p0i -e 's/^/$line\n/;' '$file'":
        unless      => "/bin/grep -Fxqe '$line' '$file'",
        path        => "/bin",
        refreshonly => $refreshonly,
    }
    
}