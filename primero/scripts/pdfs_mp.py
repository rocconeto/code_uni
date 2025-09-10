import fitz  # PyMuPDF

def split_pdf(input_pdf, output_pdf):
    doc = fitz.open(input_pdf)
    new_doc = fitz.open()

    for page in doc:
        pix = page.get_pixmap()
        w, h = pix.width // 2, pix.height // 2  # Dividimos en 4 partes

        coords = [(0, 0, w, h), (w, 0, 2*w, h), (0, h, w, 2*h), (w, h, 2*w, 2*h)]

        for x0, y0, x1, y1 in coords:
            new_page = new_doc.new_page(width=w, height=h)
            new_page.insert_image(new_page.rect, pixmap=pix, clip=(x0, y0, x1, y1))

    new_doc.save(output_pdf)
    new_doc.close()

split_pdf("input.pdf", "output.pdf")

unsplitted_pdf_name = input("Introduce el nombre del archivo del pdf:\n")
splitted_pdf_name = input("Introduce el nombre que va a tener el pdf corregidoo: ")

split_pdf(unsplitted_pdf_name, splitted_pdf_name)
