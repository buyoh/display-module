require 'selenium-webdriver'
require 'mini_magick'

options = Selenium::WebDriver::Chrome::Options.new
options.add_argument('--ignore-certificate-errors')
options.add_argument('--disable-popup-blocking')
options.add_argument('--disable-translate')
options.add_argument('--headless')

driver = Selenium::WebDriver.for(:chrome, options: options)
driver.manage.window.size = Selenium::WebDriver::Dimension.new(400, 300)

driver.get('http://127.0.0.1:8000')

warn 'webdriver started'
sleep 5

loop do
  warn 'sendimage start'
  scr_png = driver.screenshot_as(:png)
  # image = MiniMagick::Image.open('1.png')
  image = MiniMagick::Image.read(scr_png)
  # image.resize '100x100'
  # image.format 'jpg' # TODO: BGRA
  # image.write 'output.png'

  image.resize '400x300'
  image.format 'GRAY'
  image.write '1.raw'
  STDOUT.print image.to_blob
  STDOUT.flush
  warn 'sendimage done'
  sleep 30
end
