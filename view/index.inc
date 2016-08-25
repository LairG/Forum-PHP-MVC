<?php
require_once 'parts/header.inc';
?>
<section>
    
    <?php
   

    foreach ($tabCategorie as $categorie) {

        echo  $categorie->formatCategorieForindex();
        
    }
    ?>
</section>   
<?php
require_once 'parts/footer.inc';
?>