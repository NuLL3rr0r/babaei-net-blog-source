package main

import (
	"fmt"
	"net/http"
	"net/url"
)

func handleRequest(w http.ResponseWriter, r *http.Request) {
	api := "https://search.babaei.net"
	q := url.QueryEscape(fmt.Sprintf("%s site:%s", r.FormValue("q"), r.Host))
	categories := "general"
	language := "en-US"
	locale := "en"
	time_range := ""

	newUrl := fmt.Sprintf("%s/?q=%s&categories=%s&language=%s&locale=%s&time_range=%s",
		api, q, categories, language, locale, time_range)

	http.Redirect(w, r, newUrl, http.StatusSeeOther)
}

func main() {
	http.HandleFunc("/", handleRequest)
	http.ListenAndServe(":9999", nil)
}
