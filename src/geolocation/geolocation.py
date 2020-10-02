import GeoIP
import requests
import shutil
import gzip
import os

GEOIP_DB_FILE = "data/GeoIP.dat"

class GeoLocation:
    @staticmethod
    def get_country_by_name(name):
        g = GeoIP.open(GEOIP_DB_FILE, GeoIP.GEOIP_STANDARD)
        return g.country_code_by_name(name)

    @staticmethod
    def get_country_by_address(address):
        g = GeoIP.open(GEOIP_DB_FILE, GeoIP.GEOIP_STANDARD)
        return g.country_code_by_addr(address)
