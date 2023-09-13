
import pytest
import requests
import json

port = "3010"
server1_url = "http://localhost:" + port
server2_url = "http://localhost:9000"

def test_get_root():
    res = requests.get(server1_url )
    assert res.status_code == 200

def test_404_at_root_location():
    res = requests.get(server1_url + "/test.txt")
    assert res.status_code == 404

def test_404_at_another_directory():
    res = requests.get(server1_url + "/not_exist/")
    assert res.status_code == 404

def test_redirect():
    res = requests.get(server1_url + "/redirect")
    assert res.status_code == 301

def test_not_allowed_method_server():
    res = requests.put(server1_url)
    assert res.status_code == 405

def test_not_allowed_method_location():
    res = requests.patch(server1_url)
    assert res.status_code == 405

def test_directory_listing():
    res = requests.get(server1_url + "/listfile")
    expected = '<html><head><title>Index of ./www/listfile</title></head><body><h1>Index of ./www/listfile</h1><a href="/listfile/file.html">file.html</a><br><a href="/listfile/test.txt">test.txt</a><br></body></html>'

    assert res.text == expected

def test_directory_listing_not_allowed():
    res = requests.get(server1_url + "/notlistfile")
    assert res.status_code == 404

def test_configured_404_page():
    res = requests.get(server1_url + "/not_found")
    expected = ""
    for line in open("www/404.html"):
        expected += line

    assert res.text == expected

def test_configured_405_page():
    res = requests.delete(server1_url)
    expected = ""
    for line in open("www/405.html"):
        expected += line
        
    assert res.text == expected

def test_post_method():
    url = server1_url + "/teste2"
    body = json.dumps({u'body': u'Sounds great! Ill get right on it!'})

    res = requests.post(url, data=body)
    assert res.status_code == 201

def test_body_too_large():
    body = ""
    for i in range(101):
        body += str(i%10)
    res = requests.get(server1_url, data=body)

    assert res.status_code == 413

def test_second_server():
    url = server2_url
    res = requests.get(url)
    expected = ""
    for line in open("www/hello.html"):
        expected += line.strip('\n')

    assert res.text == expected
