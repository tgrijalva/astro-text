require 'rubygems'
require 'wav-file'
require "~/Code/Ruby/ruby_applications/signals_framework/signals.rb"

file_count = 0
ARGV.each do |a|
  
  if (File.exist?(a))
    file_count += 1
    puts "Processing File " + file_count.to_s + ": #{a}"

    # parameters
    # the sound file for converting
    sound_file = a
    # volume scale factor must be equal or less than 1.0
    volume_scale = 1.00

    #  program start here
    # create file name
    file_name = sound_file.split('/').last.split('.').first + "Sound"
    puts file_name

    f = open(sound_file)
    format = WavFile::readFormat(f)
    dataChunk = WavFile::readDataChunk(f)
    f.close

    puts format

    bit = 's*' if format.bitPerSample == 16 # int16_t
    bit = 'c*' if format.bitPerSample == 8 # signed char
    wavs = dataChunk.data.unpack(bit) # read binary

    # convert to 8-bit unsigned
    if (format.bitPerSample == 16)
      puts "converting to 8-bit"
      wavs.map! {|sample| (sample + 32768) >> 8}
    elsif (format.bitPerSample == 8)
      puts "converting 8-bits to unsigned"
      wavs.map! {|sample| (sample + 128)}
    end

    # volume scale if neccessary
    if (volume_scale < 1.0)
      puts "volume scaled to " + volume_scale.to_s
      wavs.map! {|sample| (sample * volume_scale).floor}
    end

    num_samples = wavs.length
    newSignal = wavs
    # convert to 20 kHz
    if (format.hz != 20000)
      puts "converting to 20 kHz"
      num_samples = ((20000 * wavs.length) / format.hz).floor
      newSignal = stretch_signal(wavs, num_samples)
    end


    # create header file
    File.open("./sounds/" + file_name.downcase + ".h", 'w') do |f|
      # header
      f.write("#ifndef " + file_name.upcase + "_H\n")
      f.write("#define " + file_name.upcase + "_H\n\n")

      f.write("#include <avr/pgmspace.h>\n\n")

      # code
      f.write("u16 get" + file_name[0, 1].upcase + file_name[1, file_name.length-1] + "Length();\n")
      f.write("u08 get" + file_name[0, 1].upcase + file_name[1, file_name.length-1] + "Sample(u16 n);\n\n")

      # footer
      f.write("#endif //ifndef " + file_name.upcase + "_H")
    end

    #  create implemetation file
    File.open("./sounds/" + file_name.downcase + ".c", 'w') do |f|
      # header
      f.write("#include \"../globals.h\"\n")
      f.write("#include \"" + file_name.downcase + ".h\"\n\n")

      # code
      f.write("volatile u16 " + file_name + "Length = " + num_samples.to_s + ";\n")
      f.write("const u08 " + file_name + "Samples[] PROGMEM = {\n")
      # sample write loop
      (num_samples - 1).times do |i|
        f.write("   " + newSignal[i].to_s + ",\n")
      end
      f.write("   " + newSignal[num_samples - 1].to_s + "\n")
      # end sample write loop
      f.write("};\n\n")

      f.write("u16 get" + file_name[0, 1].upcase + file_name[1, file_name.length-1] + "Length() {\n")
      f.write("   return " + file_name + "Length;\n")
      f.write("}\n\n")

      f.write("u08 get" + file_name[0, 1].upcase + file_name[1, file_name.length-1] + "Sample(u16 n) {\n")
      f.write("   return pgm_read_byte(&" + file_name + "Samples[n]);\n")
      f.write("}")
    end
  else
    puts "File not Found:#{a}"
  end
  
end