
import pytest
import requests
import json

port = "3011"
server1_url = "http://localhost:" + port

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
    res = requests.post(server1_url)
    assert res.status_code == 405

def test_directory_listing():
    res = requests.get(server1_url + "/listfile")
    expected = '<html><head><title>Index of ./www/listfile</title></head><body><h1>Index of ./www/listfile</h1><a href="/listfile/file.html">file.html</a><br><a href="/listfile/test.txt">test.txt</a><br></body></html>'

    assert res.text == expected

def test_directory_listing_not_allowed():
    res = requests.get(server1_url + "/notlistfile")
    assert res.status_code == 404

# TODO ??
# def test_post_method():
#     url = server1_url + "/teste2"
#     body = json.dumps({u'body': u'Sounds great! Ill get right on it!'})
#     # headers = {
#     #     'Content-Type': 'text/plain',
#     #     'Content-Length': '14'
#     # }

#     res = requests.post(url, data = body)  
#     assert res.status_code == 201
