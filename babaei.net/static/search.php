<?php
    $site = "www.babaei.net";
    $api = "https://search.babaei.net";
    $categories = "general";
    $language = "en-US";
    $locale = "en";
    $time_range = "";

    if (isset($_POST['q'])) {
        $q = strip_tags(trim($_POST['q']));
    } else {
        if (isset($_GET['q'])) {
            $q = strip_tags(trim($_GET['q']));
        } else {
            $q = "";
        }
    }

    $url = $api . "/?q=" . urlencode("$q site:$site") . "&categories=$categories&language=$language&locale=$locale&time_range=$time_range";

    header("Location: $url");

    die();
?>
