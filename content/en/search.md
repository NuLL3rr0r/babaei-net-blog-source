+++
title = "Search"
+++

In order to search the site, enter a phrase in the following text box and hit enter, please:

<br />

<div style="display: flex; align-items: center;">
    <div class="container">
        <div class="col-xs-12 col-sm-offset-1 col-sm-10 col-md-offset-2 col-md-8 col-lg-offset-2 col-lg-8">
            <form action="/search/blog" method="post">
                <div class="form-group">
                    <label for="searchInput">Search phrase</label>
                    <input class="form-control" id="searchInput" name="q" results="0" placeholder="Search…" data-_extension-text-contrast="" type="text">
                </div>
                <div style="text-align: center;">
                    <input class="btn btn-primary" type="submit" value="Search using searx">
                </div>
            </form>
        </div>
        <div class="clearfix"></div>
    </div>
</div>

<br />

_Search powered by a self-hosted instance of [searx](https://searx.me/)._
